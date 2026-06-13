from types import SimpleNamespace

import numpy as np
from opendbc.can import CANPacker
from opendbc.car import Bus, DT_CTRL
from opendbc.car.common.filter_simple import FirstOrderFilter
from opendbc.car.lateral import apply_driver_steer_torque_limits, common_fault_avoidance
from opendbc.car.interfaces import CarControllerBase
from opendbc.car.rivian.riviancan import create_lka_steering, create_longitudinal, create_wheel_touch, create_adas_status
from opendbc.car.rivian.values import CarControllerParams, RivianFlags, RivianSafetyFlags, RIVIAN_TUNE

from opendbc.sunnypilot.car.rivian.mads import MadsCarController

MAX_ANGLE_DEG = 90
MAX_ANGLE_FRAMES = 89
BLIP_FRAMES = 2
# Right turns require more torque to achieve equivalent lateral acceleration (measured asymmetry on R1T/R1S 2023)
# Above this wheel angle the rack is saturated >75% of the time (route data); cap output so the
# controller can recover from saturation faster when geometry eases
HIGH_ANGLE_THRESHOLD_DEG = 90
UNWIND_DAMPING_ANGLE_DEG = 45
UNWIND_DAMPING_MIN_TORQUE = 0.05
TORQUE_FILTER_SPEED_BP = [5., 10., 20.]
TORQUE_FILTER_RC_BP = [0.2, 0.1, 0.0]
UNWIND_FILTER_SPEED_BP = [5., 10., 15., 20.]
UNWIND_FILTER_RC_BP = [0.35, 0.25, 0.1, 0.0]


def rivian_torque_filter_rc(v_ego_raw, steering_angle_deg, raw_torque, filtered_torque):
  base_rc = float(np.interp(v_ego_raw, TORQUE_FILTER_SPEED_BP, TORQUE_FILTER_RC_BP))
  unwind_rc = float(np.interp(v_ego_raw, UNWIND_FILTER_SPEED_BP, UNWIND_FILTER_RC_BP))
  sign_reversing = raw_torque * filtered_torque < 0.
  unwinding = abs(raw_torque) < abs(filtered_torque)

  should_damp_unwind = (
    abs(steering_angle_deg) > UNWIND_DAMPING_ANGLE_DEG and
    abs(filtered_torque) > UNWIND_DAMPING_MIN_TORQUE and
    (sign_reversing or unwinding)
  )
  if should_damp_unwind:
    return max(base_rc, unwind_rc)
  return base_rc


class CarController(CarControllerBase, MadsCarController):
  def __init__(self, dbc_names, CP, CP_SP):
    CarControllerBase.__init__(self, dbc_names, CP, CP_SP)
    MadsCarController.__init__(self)
    self.apply_torque_last = 0
    self.packer = CANPacker(dbc_names[Bus.pt])
    self.angle_limit_counter = 0
    self.cancel_frames = 0
    safety_param = CP.safetyConfigs[0].safetyParam if len(CP.safetyConfigs) else 0
    self.tune = RIVIAN_TUNE[bool(safety_param & RivianSafetyFlags.AGGRESSIVE_TUNE.value)]
    self.torque_filter = FirstOrderFilter(0.0, 0.2, DT_CTRL, initialized=False)
    self.torque_limits = SimpleNamespace(
      STEER_MAX=max(self.tune['steer_max_lookup'][1]),
      STEER_DELTA_UP=self.tune['steer_delta_up'],
      STEER_DELTA_DOWN=self.tune['steer_delta_down'],
      STEER_DRIVER_ALLOWANCE=CarControllerParams.STEER_DRIVER_ALLOWANCE,
      STEER_DRIVER_MULTIPLIER=CarControllerParams.STEER_DRIVER_MULTIPLIER,
      STEER_DRIVER_FACTOR=CarControllerParams.STEER_DRIVER_FACTOR,
    )

  def update(self, CC, CC_SP, CS, now_nanos):
    MadsCarController.update(self, CC, CC_SP, CS)
    actuators = CC.actuators
    can_sends = []

    apply_torque = 0
    steer_max = round(float(np.interp(CS.out.vEgoRaw, self.tune['steer_max_lookup'][0],
                                      self.tune['steer_max_lookup'][1])))
    if self.mads.lat_active:
      if self.tune['use_torque_filter']:
        self.torque_filter.update_alpha(rivian_torque_filter_rc(
          CS.out.vEgoRaw, CS.out.steeringAngleDeg, CC.actuators.torque, self.torque_filter.x
        ))
        desired_torque = self.torque_filter.update(CC.actuators.torque)
      else:
        desired_torque = CC.actuators.torque
      new_torque = int(round(desired_torque * steer_max))
      apply_torque = apply_driver_steer_torque_limits(new_torque, self.apply_torque_last,
                                                      CS.out.steeringTorque, self.torque_limits, steer_max)
      if abs(CS.out.steeringAngleDeg) > HIGH_ANGLE_THRESHOLD_DEG:
        cap = int(round(steer_max * self.tune['high_angle_cap_frac']))
        apply_torque = max(-cap, min(cap, apply_torque))
    else:
      self.torque_filter.x = 0.0
      self.torque_filter.initialized = True

    self.angle_limit_counter, lka_act_toi = common_fault_avoidance(
      abs(CS.out.steeringAngleDeg) >= MAX_ANGLE_DEG,
      self.mads.lat_active,
      self.angle_limit_counter,
      MAX_ANGLE_FRAMES,
      BLIP_FRAMES,
    )

    blip = self.mads.lat_active and not lka_act_toi
    send_torque = 0 if blip else apply_torque
    if not blip:
      self.apply_torque_last = apply_torque

    can_sends.append(create_lka_steering(self.packer, self.frame, CS.acm_lka_hba_cmd, send_torque, CC.enabled, CC.latActive, self.mads, lka_act_toi))

    if self.frame % 5 == 0 and not (self.CP.flags & RivianFlags.GEN2):
      can_sends.append(create_wheel_touch(self.packer, CS.sccm_wheel_touch, CC.enabled))

    # Longitudinal control
    if self.CP.openpilotLongitudinalControl:
      accel = float(np.clip(actuators.accel, CarControllerParams.ACCEL_MIN, CarControllerParams.ACCEL_MAX))
      can_sends.append(create_longitudinal(self.packer, self.frame, accel, CC.enabled))
    else:
      interface_status = None
      if CC.cruiseControl.cancel:
        # if there is a noEntry, we need to send a status of "available" before the ACM will accept "unavailable"
        # send "available" right away as the VDM itself takes a few frames to acknowledge
        interface_status = 1 if self.cancel_frames < 5 else 0
        self.cancel_frames += 1
      else:
        self.cancel_frames = 0

      for msg in CS.vdm_adas_status:
        can_sends.append(create_adas_status(self.packer, msg, interface_status))

    new_actuators = actuators.as_builder()
    new_actuators.torque = apply_torque / steer_max
    new_actuators.torqueOutputCan = apply_torque

    self.frame += 1
    return new_actuators, can_sends
