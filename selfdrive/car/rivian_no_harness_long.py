from openpilot.common.constants import CV
from opendbc.sunnypilot.car.rivian.values import RivianFlagsSP

RIVIAN_MIN_SET_SPEED_MS = 20.0 * CV.MPH_TO_MS
RIVIAN_MAX_SET_SPEED_MS = 85.0 * CV.MPH_TO_MS
RIVIAN_SET_SPEED_STEP_MPH = 5.0
RIVIAN_SET_SPEED_STEP_KPH = 5.0
UI_SET_SPEED_INCREASE = "increase"
UI_SET_SPEED_DECREASE = "decrease"


def rivian_no_harness_long_active(CP, CP_SP) -> bool:
  flags = int(CP_SP.flags)
  return (CP.brand == "rivian" and CP.openpilotLongitudinalControl and
          bool(flags & RivianFlagsSP.NO_HARNESS_ALPHA_LONG.value) and
          not bool(flags & RivianFlagsSP.LONGITUDINAL_HARNESS_UPGRADE.value))


def clip_rivian_no_harness_set_speed(speed_ms: float) -> float:
  return float(max(RIVIAN_MIN_SET_SPEED_MS, min(speed_ms, RIVIAN_MAX_SET_SPEED_MS)))


def adjust_rivian_no_harness_set_speed(speed_ms: float, action: str, is_metric: bool) -> float:
  delta = RIVIAN_SET_SPEED_STEP_KPH * CV.KPH_TO_MS if is_metric else RIVIAN_SET_SPEED_STEP_MPH * CV.MPH_TO_MS
  if action == UI_SET_SPEED_INCREASE:
    speed_ms += delta
  elif action == UI_SET_SPEED_DECREASE:
    speed_ms -= delta
  return clip_rivian_no_harness_set_speed(speed_ms)
