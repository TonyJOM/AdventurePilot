import unittest

from opendbc.car import get_safety_config, structs
from opendbc.car.rivian.values import RivianFlags, RivianSafetyFlags, CAR
from opendbc.sunnypilot.car.rivian.values import RivianFlagsSP
from opendbc.sunnypilot.car.interfaces import _initialize_rivian


def _aggressive(fingerprint: str, gen2: bool = False, override: int = 0) -> bool:
  CP = structs.CarParams()
  CP.brand = "rivian"
  CP.carFingerprint = fingerprint
  CP.flags = RivianFlags.GEN2.value if gen2 else 0
  CP_SP = structs.CarParamsSP()
  _initialize_rivian(CP, CP_SP, {"RivianAggressiveTune": override})
  return bool(CP_SP.flags & RivianFlagsSP.AGGRESSIVE_TUNE.value)


R1T = CAR.RIVIAN_R1T
R1S = CAR.RIVIAN_R1S


def _rivian_cp(fingerprint: str = R1T, gen2: bool = False) -> structs.CarParams:
  CP = structs.CarParams()
  CP.brand = "rivian"
  CP.carFingerprint = fingerprint
  CP.flags = RivianFlags.GEN2.value if gen2 else 0
  CP.safetyConfigs = [get_safety_config(structs.CarParams.SafetyModel.rivian)]
  return CP


class TestRivianTuneSelection(unittest.TestCase):
  def test_auto_selection(self):
    # Auto (override 0): aggressive ONLY for a Gen1 R1T; everything else stays tame.
    self.assertTrue(_aggressive(R1T), "Gen1 R1T should auto-select aggressive")
    self.assertFalse(_aggressive(R1S), "R1S should stay tame")
    self.assertFalse(_aggressive(R1T, gen2=True), "Gen2 R1T should stay tame (no data)")

  def test_manual_tame_override(self):
    # Aggressive is not user-selectable; override 1 forces tame, even on a Gen1 R1T.
    self.assertFalse(_aggressive(R1T, override=1), "override 1 forces tame on a Gen1 R1T")
    self.assertFalse(_aggressive(R1S, override=1), "override 1 keeps an R1S tame")

  def test_non_rivian_is_noop(self):
    CP = structs.CarParams()
    CP.brand = "toyota"
    CP_SP = structs.CarParamsSP()
    _initialize_rivian(CP, CP_SP, {})
    self.assertFalse(CP_SP.flags & RivianFlagsSP.AGGRESSIVE_TUNE.value)


class TestRivianNoHarnessAlphaLong(unittest.TestCase):
  def test_no_harness_flag_off_is_unavailable(self):
    CP = _rivian_cp()
    CP_SP = structs.CarParamsSP()

    _initialize_rivian(CP, CP_SP, {"RivianNoHarnessAlphaLong": 0, "AlphaLongitudinalEnabled": 0})

    self.assertFalse(CP.alphaLongitudinalAvailable)
    self.assertFalse(CP.openpilotLongitudinalControl)
    self.assertFalse(CP_SP.flags & RivianFlagsSP.NO_HARNESS_ALPHA_LONG.value)

  def test_missing_params_are_treated_as_disabled(self):
    CP = _rivian_cp()
    CP_SP = structs.CarParamsSP()

    _initialize_rivian(CP, CP_SP, {"RivianAggressiveTune": None,
                                   "RivianNoHarnessAlphaLong": None,
                                   "AlphaLongitudinalEnabled": None})

    self.assertFalse(CP.alphaLongitudinalAvailable)
    self.assertFalse(CP.openpilotLongitudinalControl)
    self.assertFalse(CP_SP.flags & RivianFlagsSP.NO_HARNESS_ALPHA_LONG.value)

  def test_no_harness_flag_makes_alpha_available_without_arming_long(self):
    CP = _rivian_cp()
    CP.radarUnavailable = False
    CP.enableBsm = True
    CP_SP = structs.CarParamsSP()

    _initialize_rivian(CP, CP_SP, {"RivianNoHarnessAlphaLong": 1, "AlphaLongitudinalEnabled": 0})

    self.assertTrue(CP.alphaLongitudinalAvailable)
    self.assertFalse(CP.openpilotLongitudinalControl)
    self.assertTrue(CP.radarUnavailable)
    self.assertFalse(CP.enableBsm)
    self.assertTrue(CP_SP.flags & RivianFlagsSP.NO_HARNESS_ALPHA_LONG.value)
    self.assertFalse(CP_SP.flags & RivianFlagsSP.LONGITUDINAL_HARNESS_UPGRADE.value)

  def test_no_harness_alpha_enabled_arms_op_long(self):
    CP = _rivian_cp()
    CP_SP = structs.CarParamsSP()

    _initialize_rivian(CP, CP_SP, {"RivianNoHarnessAlphaLong": 1, "AlphaLongitudinalEnabled": 1})

    self.assertTrue(CP.alphaLongitudinalAvailable)
    self.assertTrue(CP.openpilotLongitudinalControl)
    self.assertTrue(CP.safetyConfigs[0].safetyParam & RivianSafetyFlags.LONG_CONTROL.value)

  def test_real_harness_wins_over_no_harness_flag(self):
    CP = _rivian_cp()
    CP.alphaLongitudinalAvailable = True
    CP.radarUnavailable = False
    CP.enableBsm = True
    CP_SP = structs.CarParamsSP()
    CP_SP.flags |= RivianFlagsSP.LONGITUDINAL_HARNESS_UPGRADE.value

    _initialize_rivian(CP, CP_SP, {"RivianNoHarnessAlphaLong": 1, "AlphaLongitudinalEnabled": 0})

    self.assertTrue(CP.alphaLongitudinalAvailable)
    self.assertFalse(CP.openpilotLongitudinalControl)
    self.assertFalse(CP.radarUnavailable)
    self.assertTrue(CP.enableBsm)
    self.assertTrue(CP_SP.flags & RivianFlagsSP.LONGITUDINAL_HARNESS_UPGRADE.value)
    self.assertFalse(CP_SP.flags & RivianFlagsSP.NO_HARNESS_ALPHA_LONG.value)

  def test_gen2_cannot_enable_no_harness_alpha_long(self):
    CP = _rivian_cp(gen2=True)
    CP_SP = structs.CarParamsSP()

    _initialize_rivian(CP, CP_SP, {"RivianNoHarnessAlphaLong": 1, "AlphaLongitudinalEnabled": 1})

    self.assertFalse(CP.alphaLongitudinalAvailable)
    self.assertFalse(CP.openpilotLongitudinalControl)
    self.assertFalse(CP_SP.flags & RivianFlagsSP.NO_HARNESS_ALPHA_LONG.value)


if __name__ == "__main__":
  unittest.main()
