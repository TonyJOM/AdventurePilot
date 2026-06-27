import unittest

from opendbc.car import structs
from openpilot.common.constants import CV
from openpilot.selfdrive.car.rivian_no_harness_long import (
  UI_SET_SPEED_DECREASE,
  UI_SET_SPEED_INCREASE,
  adjust_rivian_no_harness_set_speed,
  clip_rivian_no_harness_set_speed,
  rivian_no_harness_long_active,
)
from opendbc.sunnypilot.car.rivian.values import RivianFlagsSP


class TestRivianNoHarnessLongHelpers(unittest.TestCase):
  def test_active_only_for_no_harness_rivian_op_long(self):
    CP = structs.CarParams()
    CP.brand = "rivian"
    CP.openpilotLongitudinalControl = True
    CP_SP = structs.CarParamsSP()
    CP_SP.flags = RivianFlagsSP.NO_HARNESS_ALPHA_LONG.value

    self.assertTrue(rivian_no_harness_long_active(CP, CP_SP))

    CP.openpilotLongitudinalControl = False
    self.assertFalse(rivian_no_harness_long_active(CP, CP_SP))

    CP.openpilotLongitudinalControl = True
    CP_SP.flags |= RivianFlagsSP.LONGITUDINAL_HARNESS_UPGRADE.value
    self.assertFalse(rivian_no_harness_long_active(CP, CP_SP))

  def test_adjusts_in_imperial_units(self):
    speed = 45.0 * CV.MPH_TO_MS

    increased = adjust_rivian_no_harness_set_speed(speed, UI_SET_SPEED_INCREASE, is_metric=False)
    decreased = adjust_rivian_no_harness_set_speed(speed, UI_SET_SPEED_DECREASE, is_metric=False)

    self.assertAlmostEqual(increased, 50.0 * CV.MPH_TO_MS)
    self.assertAlmostEqual(decreased, 40.0 * CV.MPH_TO_MS)

  def test_adjusts_in_metric_units(self):
    speed = 72.0 * CV.KPH_TO_MS

    increased = adjust_rivian_no_harness_set_speed(speed, UI_SET_SPEED_INCREASE, is_metric=True)
    decreased = adjust_rivian_no_harness_set_speed(speed, UI_SET_SPEED_DECREASE, is_metric=True)

    self.assertAlmostEqual(increased, 77.0 * CV.KPH_TO_MS)
    self.assertAlmostEqual(decreased, 67.0 * CV.KPH_TO_MS)

  def test_clips_to_rivian_bounds(self):
    self.assertAlmostEqual(clip_rivian_no_harness_set_speed(5.0 * CV.MPH_TO_MS), 20.0 * CV.MPH_TO_MS)
    self.assertAlmostEqual(clip_rivian_no_harness_set_speed(95.0 * CV.MPH_TO_MS), 85.0 * CV.MPH_TO_MS)


if __name__ == "__main__":
  unittest.main()
