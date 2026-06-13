import unittest
import math

from opendbc.car import gen_empty_fingerprint
from opendbc.car.rivian.carcontroller import rivian_torque_filter_rc
from opendbc.car.rivian.fingerprints import FW_VERSIONS
from opendbc.car.rivian.values import CAR, FW_QUERY_CONFIG, WMI, ModelLine, ModelYear, RivianFlags, RivianSafetyFlags, RIVIAN_TUNE, platform_from_vin
from opendbc.car.car_helpers import interfaces
from opendbc.car.fw_versions import match_fw_to_car
from opendbc.car.structs import CarParams


def make_vin(wmi: WMI, line: ModelLine, year: ModelYear) -> str:
  vin = ["0"] * 17
  vin[:3] = wmi
  vin[3] = line.value
  vin[8] = "1"
  vin[9] = year.value
  return "".join(vin)


def make_fingerprint(gen2: bool = False) -> dict[int, dict[int, int]]:
  fingerprint = gen_empty_fingerprint()
  if not gen2:
    fingerprint[0][0x321] = 7
  return fingerprint


class TestRivian(unittest.TestCase):
  def test_custom_fuzzy_fingerprinting(self):
    cases = [
      (make_vin(WMI.RIVIAN_TRUCK, ModelLine.R1T, ModelYear.P_2023), CAR.RIVIAN_R1T),
      (make_vin(WMI.RIVIAN_MPV, ModelLine.R1S, ModelYear.P_2023), CAR.RIVIAN_R1S),
    ]
    for vin, platform in cases:
      with self.subTest(platform=platform.name):
        assert platform_from_vin(vin) == platform
        assert FW_QUERY_CONFIG.match_fw_to_car_fuzzy({}, vin, FW_VERSIONS) == {platform}

  def test_invalid_vins_do_not_match(self):
    invalid_vins = [
      "0" * 17,
      make_vin(WMI.RIVIAN_TRUCK, ModelLine.R1S, ModelYear.P_2023),
      make_vin(WMI.RIVIAN_MPV, ModelLine.R1T, ModelYear.P_2023),
      make_vin(WMI.RIVIAN_TRUCK, ModelLine.R1T, ModelYear.T_2026),
    ]
    for vin in invalid_vins:
      with self.subTest(vin=vin):
        assert platform_from_vin(vin) is None
        assert FW_QUERY_CONFIG.match_fw_to_car_fuzzy({}, vin, FW_VERSIONS) == set()

  def test_shared_firmware_disambiguates_with_vin(self):
    for platform, vin in (
      (CAR.RIVIAN_R1S, make_vin(WMI.RIVIAN_MPV, ModelLine.R1S, ModelYear.P_2023)),
      (CAR.RIVIAN_R1T, make_vin(WMI.RIVIAN_TRUCK, ModelLine.R1T, ModelYear.P_2023)),
    ):
      car_fw = [
        CarParams.CarFw(ecu=ecu, fwVersion=versions[0], brand="rivian", address=addr, subAddress=0 if sub_addr is None else sub_addr)
        for (ecu, addr, sub_addr), versions in FW_VERSIONS[platform].items()
      ]
      _, matches = match_fw_to_car(car_fw, vin, allow_exact=True, allow_fuzzy=False)
      assert matches == {platform}

  def test_r1s_r1t_geometry_and_torque_params(self):
    for platform, wheelbase, friction in ((CAR.RIVIAN_R1S, 3.08, 0.07), (CAR.RIVIAN_R1T, 3.449, 0.10)):
      CP = interfaces[platform].get_non_essential_params(platform)
      assert math.isclose(CP.wheelbase, wheelbase, rel_tol=0, abs_tol=1e-6)
      assert math.isclose(CP.lateralTuning.torque.latAccelFactor, 2.8, rel_tol=0, abs_tol=1e-6)
      assert math.isclose(CP.lateralTuning.torque.friction, friction, rel_tol=0, abs_tol=1e-6)

  def test_aggressive_tune_safety_flag_selection(self):
    cases = (
      (CAR.RIVIAN_R1T, False, True),
      (CAR.RIVIAN_R1T, True, False),
      (CAR.RIVIAN_R1S, False, False),
      (CAR.RIVIAN_R1S, True, False),
    )
    for platform, gen2, aggressive_expected in cases:
      with self.subTest(platform=platform.name, gen2=gen2):
        CP = interfaces[platform].get_params(platform, make_fingerprint(gen2), list(), False, False, False)
        assert bool(CP.flags & RivianFlags.GEN2.value) == gen2
        aggressive = bool(CP.safetyConfigs[0].safetyParam & RivianSafetyFlags.AGGRESSIVE_TUNE.value)
        assert aggressive == aggressive_expected

  def test_aggressive_tune_safety_flag_composes_with_long_control(self):
    CP = interfaces[CAR.RIVIAN_R1T].get_params(CAR.RIVIAN_R1T, make_fingerprint(), list(), True, False, False)
    assert CP.safetyConfigs[0].safetyParam & RivianSafetyFlags.AGGRESSIVE_TUNE.value
    assert CP.safetyConfigs[0].safetyParam & RivianSafetyFlags.LONG_CONTROL.value

  def test_aggressive_tune_is_low_speed_only(self):
    assert RIVIAN_TUNE[True]['steer_max_lookup'] == ([9, 13, 25, 27], [460, 350, 295, 275])
    assert RIVIAN_TUNE[True]['high_angle_cap_frac'] == 1.0
    assert RIVIAN_TUNE[False]['steer_max_lookup'] == ([9, 13, 25, 27], [385, 350, 295, 275])
    assert RIVIAN_TUNE[False]['high_angle_cap_frac'] == 0.95

  def test_aggressive_torque_filter_unwind_damping(self):
    cases = (
      ("turn_in_high_angle", 10., 70., 0.4, 0.2, 0.1),
      ("same_sign_unwind_high_angle", 10., 70., 0.1, 0.3, 0.25),
      ("sign_reversal_high_angle", 10., 70., -0.1, 0.3, 0.25),
      ("low_angle_unwind", 10., 20., 0.1, 0.3, 0.1),
      ("near_zero_filtered_torque", 10., 70., 0., 0.04, 0.1),
      ("high_speed_unwind", 20., 70., 0., 0.3, 0.0),
    )
    for name, v_ego_raw, steering_angle_deg, raw_torque, filtered_torque, expected_rc in cases:
      with self.subTest(name=name):
        rc = rivian_torque_filter_rc(v_ego_raw, steering_angle_deg, raw_torque, filtered_torque)
        assert math.isclose(rc, expected_rc, rel_tol=0, abs_tol=1e-6)
