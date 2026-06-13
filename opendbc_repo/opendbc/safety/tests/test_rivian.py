#!/usr/bin/env python3
import unittest

from opendbc.car.structs import CarParams
from opendbc.safety.tests.libsafety import libsafety_py
import opendbc.safety.tests.common as common
from opendbc.safety.tests.common import CANPackerSafety
from opendbc.car.rivian.values import RivianSafetyFlags
from opendbc.car.rivian.riviancan import checksum as _checksum

RIVIAN_MADS_STALK_DOWN_MAX_SPEED = 20 * 0.44704
RIVIAN_ACM_FEATURE_STATUS_STANDBY = 0
RIVIAN_ACM_FEATURE_STATUS_ACC = 1
RIVIAN_ACM_FEATURE_STATUS_HWP = 2
RIVIAN_PRNDL_PARK = 1
RIVIAN_PRNDL_DRIVE = 4
RIVIAN_USER_ADAS_REQUEST_IDLE = 0
RIVIAN_USER_ADAS_REQUEST_UP_1 = 1
RIVIAN_USER_ADAS_REQUEST_DOWN_1 = 3
RIVIAN_USER_ADAS_REQUEST_DOWN_2 = 4


def checksum(msg):
  addr, dat, bus = msg
  ret = bytearray(dat)

  # ESP_Status
  if addr == 0x208:
    ret[0] = _checksum(ret[1:], 0x1D, 0xB1)
  elif addr == 0x150:
    ret[0] = _checksum(ret[1:], 0x1D, 0x9A)
  elif addr == 0x162:
    ret[0] = _checksum(ret[1:], 0x1D, 0xD1)

  return addr, ret, bus


class TestRivianSafetyBase(common.CarSafetyTest, common.DriverTorqueSteeringSafetyTest, common.SteerRequestCutSafetyTest,
                           common.LongitudinalAccelSafetyTest, common.VehicleSpeedSafetyTest):

  TX_MSGS = [[0x120, 0], [0x321, 2], [0x162, 2]]
  RELAY_MALFUNCTION_ADDRS = {0: (0x120,), 2: (0x321, 0x162)}
  FWD_BLACKLISTED_ADDRS = {0: [0x321, 0x162], 2: [0x120]}

  MAX_TORQUE_LOOKUP = [9, 25, 27], [385, 295, 275]
  DYNAMIC_MAX_TORQUE = True
  MAX_RATE_UP = 3
  MAX_RATE_DOWN = 5

  MAX_RT_DELTA = 125

  DRIVER_TORQUE_ALLOWANCE = 100
  DRIVER_TORQUE_FACTOR = 2

  MIN_VALID_STEERING_FRAMES = 89
  MAX_INVALID_STEERING_FRAMES = 2

  cnt_speed = 0
  cnt_speed_2 = 0
  cnt_adas = 0

  def _torque_driver_msg(self, torque):
    values = {"EPAS_TorsionBarTorque": torque / 100.0}
    return self.packer.make_can_msg_safety("EPAS_SystemStatus", 0, values)

  def _torque_cmd_msg(self, torque, steer_req=1):
    values = {"ACM_lkaStrToqReq": torque, "ACM_lkaActToi": steer_req}
    return self.packer.make_can_msg_safety("ACM_lkaHbaCmd", 0, values)

  def _speed_msg(self, speed, quality_flag=True):
    values = {"ESP_Vehicle_Speed": speed * 3.6, "ESP_Status_Counter": self.cnt_speed % 15,
              "ESP_Vehicle_Speed_Q": 1 if quality_flag else 0}
    self.__class__.cnt_speed += 1
    return self.packer.make_can_msg_safety("ESP_Status", 0, values, fix_checksum=checksum)

  def _speed_msg_2(self, speed, quality_flag=True):
    # Rivian has a dynamic max torque limit based on speed, so it checks two sources
    return self._user_gas_msg(0, speed, quality_flag)

  def _user_brake_msg(self, brake):
    values = {"iBESP2_BrakePedalApplied": brake}
    return self.packer.make_can_msg_safety("iBESP2", 0, values)

  def _user_gas_msg(self, gas, speed=0, quality_flag=True, gear=RIVIAN_PRNDL_DRIVE):
    values = {"VDM_AcceleratorPedalPosition": gas, "VDM_VehicleSpeed": speed * 3.6,
              "VDM_Prndl_Status": gear,
              "VDM_PropStatus_Counter": self.cnt_speed_2 % 15, "VDM_VehicleSpeedQ": 1 if quality_flag else 0}
    self.__class__.cnt_speed_2 += 1
    return self.packer.make_can_msg_safety("VDM_PropStatus", 0, values, fix_checksum=checksum)

  def _pcm_status_msg(self, enable):
    values = {"ACM_FeatureStatus": enable, "ACM_Unkown1": 1}
    return self.packer.make_can_msg_safety("ACM_Status", 2, values)

  def _adas_status_msg(self, user_adas_request):
    values = {
      "VDM_AdasStatus_Counter": self.cnt_adas % 15,
      "VDM_UserAdasRequest": user_adas_request,
    }
    self.__class__.cnt_adas += 1
    return self.packer.make_can_msg_safety("VDM_AdasSts", 0, values, fix_checksum=checksum)

  def _accel_msg(self, accel: float):
    values = {"ACM_AccelerationRequest": accel}
    return self.packer.make_can_msg_safety("ACM_longitudinalRequest", 0, values)

  def _setup_mads_stalk_down(self, speed=0, brake=False, feature_status=RIVIAN_ACM_FEATURE_STATUS_STANDBY,
                             gear=RIVIAN_PRNDL_DRIVE, enable_mads=True):
    self.safety.set_mads_params(enable_mads, False, False)
    self._rx(self._speed_msg(speed))
    self._rx(self._speed_msg_2(speed))
    self._rx(self._user_gas_msg(0, speed, gear=gear))
    self._rx(self._user_brake_msg(brake))
    self._rx(self._pcm_status_msg(feature_status))
    self._rx(self._adas_status_msg(RIVIAN_USER_ADAS_REQUEST_IDLE))
    self.safety.set_controls_allowed(False)
    self.safety.set_controls_allowed_lateral(False)

  def _stalk_down(self, request=RIVIAN_USER_ADAS_REQUEST_DOWN_2):
    self._rx(self._adas_status_msg(request))

  def test_single_stalk_down_enables_mads_lateral(self):
    for request in (RIVIAN_USER_ADAS_REQUEST_DOWN_1, RIVIAN_USER_ADAS_REQUEST_DOWN_2):
      with self.subTest(request=request):
        self._setup_mads_stalk_down()

        self._stalk_down(request)

        self.assertTrue(self.safety.get_controls_allowed_lateral())

  def test_non_down_stalk_request_does_not_enable_mads_lateral(self):
    self._setup_mads_stalk_down()

    self._rx(self._adas_status_msg(RIVIAN_USER_ADAS_REQUEST_UP_1))

    self.assertFalse(self.safety.get_controls_allowed_lateral())

  def test_held_stalk_down_does_not_retrigger_mads_lateral(self):
    self._setup_mads_stalk_down()

    self._stalk_down()
    self.assertTrue(self.safety.get_controls_allowed_lateral())
    self.safety.set_controls_allowed_lateral(False)
    self._stalk_down()

    self.assertFalse(self.safety.get_controls_allowed_lateral())

  def test_stalk_down_with_mads_disabled_does_not_enable_mads_lateral(self):
    self._setup_mads_stalk_down(enable_mads=False)

    self._stalk_down()

    self.assertFalse(self.safety.get_controls_allowed_lateral())

  def test_stalk_down_with_brake_pressed_does_not_enable_mads_lateral(self):
    self._setup_mads_stalk_down(brake=True)

    self._stalk_down()

    self.assertFalse(self.safety.get_controls_allowed_lateral())

  def test_stalk_down_with_acc_or_hwp_active_does_not_enable_mads_lateral(self):
    for feature_status in (RIVIAN_ACM_FEATURE_STATUS_ACC, RIVIAN_ACM_FEATURE_STATUS_HWP):
      with self.subTest(feature_status=feature_status):
        self._setup_mads_stalk_down(feature_status=feature_status)

        self._stalk_down()

        self.assertFalse(self.safety.get_controls_allowed_lateral())

  def test_stalk_down_out_of_drive_does_not_enable_mads_lateral(self):
    self._setup_mads_stalk_down(gear=RIVIAN_PRNDL_PARK)

    self._stalk_down()

    self.assertFalse(self.safety.get_controls_allowed_lateral())

  def test_stalk_down_at_acc_speed_does_not_enable_mads_lateral(self):
    self._setup_mads_stalk_down(speed=RIVIAN_MADS_STALK_DOWN_MAX_SPEED)

    self._stalk_down()

    self.assertFalse(self.safety.get_controls_allowed_lateral())

  def test_stalk_down_after_idle_can_enable_mads_lateral_again(self):
    self._setup_mads_stalk_down()

    self._stalk_down()
    self.assertTrue(self.safety.get_controls_allowed_lateral())
    self.safety.set_controls_allowed_lateral(False)
    self._rx(self._adas_status_msg(RIVIAN_USER_ADAS_REQUEST_IDLE))
    self._stalk_down()

    self.assertTrue(self.safety.get_controls_allowed_lateral())

  def test_wheel_touch(self):
    # For hiding hold wheel alert on engage
    for controls_allowed in (True, False):
      self.safety.set_controls_allowed(controls_allowed)
      values = {
        "SCCM_WheelTouch_HandsOn": 1 if controls_allowed else 0,
        "SCCM_WheelTouch_CapacitiveValue": 100 if controls_allowed else 0,
        "SETME_X52": 100,
      }
      self.assertTrue(self._tx(self.packer.make_can_msg_safety("SCCM_WheelTouch", 2, values)))

  def test_rx_hook(self):
    # checksum, counter, and quality flag checks
    for quality_flag in (True, False):
      for msg_type in ("speed", "speed_2"):
        self.safety.set_controls_allowed(True)
        # send multiple times to verify counter checks
        for _ in range(10):
          if msg_type == "speed":
            msg = self._speed_msg(0, quality_flag=quality_flag)
          elif msg_type == "speed_2":
            msg = self._speed_msg_2(0, quality_flag=quality_flag)

          self.assertEqual(quality_flag, self._rx(msg))
          self.assertEqual(quality_flag, self.safety.get_controls_allowed())

        # Mess with checksum to make it fail
        msg[0].data[0] = 0xff
        self.assertFalse(self._rx(msg))
        self.assertFalse(self.safety.get_controls_allowed())


class TestRivianStockSafety(TestRivianSafetyBase):

  LONGITUDINAL = False

  def setUp(self):
    self.packer = CANPackerSafety("rivian_primary_actuator")
    self.safety = libsafety_py.libsafety
    self.safety.set_safety_hooks(CarParams.SafetyModel.rivian, 0)
    self.safety.init_tests()

  def test_adas_status(self):
    # For canceling stock ACC
    for controls_allowed in (True, False):
      self.safety.set_controls_allowed(controls_allowed)
      for interface_status in range(4):
        values = {"VDM_AdasInterfaceStatus": interface_status}
        self.assertTrue(self._tx(self.packer.make_can_msg_safety("VDM_AdasSts", 2, values)))

  def test_aggressive_torque_rejected_without_flag(self):
    self._reset_speed_measurement(9)
    self.safety.set_controls_allowed(True)
    self._set_prev_torque(385)
    self.assertFalse(self._tx(self._torque_cmd_msg(386)))

  def _set_aggressive_safety_hooks(self):
    self.safety.set_safety_hooks(CarParams.SafetyModel.rivian, RivianSafetyFlags.AGGRESSIVE_TUNE)
    self.safety.init_tests()

  def test_aggressive_torque_limits(self):
    self._set_aggressive_safety_hooks()
    self.safety.set_controls_allowed(True)

    self._reset_speed_measurement(9)
    self._set_prev_torque(460)
    self.assertTrue(self._tx(self._torque_cmd_msg(460)))
    self.assertFalse(self._tx(self._torque_cmd_msg(461)))

    self._reset_speed_measurement(26)
    self._set_prev_torque(325)
    self.assertTrue(self._tx(self._torque_cmd_msg(325)))
    self.assertFalse(self._tx(self._torque_cmd_msg(327)))

  def test_aggressive_torque_rates(self):
    self._set_aggressive_safety_hooks()
    self.safety.set_controls_allowed(True)

    self._set_prev_torque(0)
    self.assertTrue(self._tx(self._torque_cmd_msg(4)))
    self._set_prev_torque(0)
    self.assertFalse(self._tx(self._torque_cmd_msg(5)))

    self._reset_speed_measurement(9)
    self._set_prev_torque(460)
    self._reset_torque_driver_measurement(-321)
    self.assertTrue(self._tx(self._torque_cmd_msg(453)))
    self._set_prev_torque(460)
    self._reset_torque_driver_measurement(-321)
    self.assertFalse(self._tx(self._torque_cmd_msg(454)))


class TestRivianLongitudinalSafety(TestRivianSafetyBase):

  TX_MSGS = [[0x120, 0], [0x321, 2], [0x160, 0]]
  RELAY_MALFUNCTION_ADDRS = {0: (0x120, 0x160), 2: (0x321,)}
  FWD_BLACKLISTED_ADDRS = {0: [0x321], 2: [0x120, 0x160]}

  def setUp(self):
    self.packer = CANPackerSafety("rivian_primary_actuator")
    self.safety = libsafety_py.libsafety
    self.safety.set_safety_hooks(CarParams.SafetyModel.rivian, RivianSafetyFlags.LONG_CONTROL)
    self.safety.init_tests()


if __name__ == "__main__":
  unittest.main()
