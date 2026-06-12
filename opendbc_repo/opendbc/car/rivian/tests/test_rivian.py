import unittest
import math

from opendbc.car.rivian.fingerprints import FW_VERSIONS
from opendbc.car.rivian.values import CAR, FW_QUERY_CONFIG, WMI, ModelLine, ModelYear, platform_from_vin
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
    for platform, wheelbase in ((CAR.RIVIAN_R1S, 3.08), (CAR.RIVIAN_R1T, 3.449)):
      CP = interfaces[platform].get_non_essential_params(platform)
      assert math.isclose(CP.wheelbase, wheelbase, rel_tol=0, abs_tol=1e-6)
      assert math.isclose(CP.lateralTuning.torque.latAccelFactor, 2.8, rel_tol=0, abs_tol=1e-6)
      assert math.isclose(CP.lateralTuning.torque.friction, 0.07, rel_tol=0, abs_tol=1e-6)
