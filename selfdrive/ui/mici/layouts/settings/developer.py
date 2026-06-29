import os
import socket

from openpilot.common.basedir import BASEDIR
from openpilot.common.time_helpers import system_time_valid
from openpilot.system.ui.widgets.scroller import NavScroller
from openpilot.selfdrive.ui.mici.widgets.button import BigButton, BigToggle, BigParamControl, BigCircleParamControl, BigMultiParamToggle
from openpilot.selfdrive.ui.mici.widgets.dialog import BigDialog, BigInputDialog
from openpilot.selfdrive.ui.mici.layouts.settings.branch_selector import BranchSelectorMici
from openpilot.system.ui.lib.application import gui_app
from openpilot.selfdrive.ui.layouts.settings.common import restart_needed_callback
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.selfdrive.ui.widgets.ssh_key import SshKeyFetcher
from opendbc.car.rivian.values import RivianFlags
from opendbc.sunnypilot.car.rivian.values import RivianFlagsSP

AP_VISUALIZER_PORT = 8077
AP_VISUALIZER_URL = f"http://ap-visualizer.local:{AP_VISUALIZER_PORT}"
AP_VISUALIZER_ROOT = os.path.join(BASEDIR, "ap_visualizer_repo")


def ap_visualizer_installed() -> bool:
  return os.path.exists(os.path.join(AP_VISUALIZER_ROOT, "ap_visualizer", "server.py")) and \
         os.path.exists(os.path.join(AP_VISUALIZER_ROOT, "dist", "index.html"))


def ap_visualizer_fallback_url() -> str:
  try:
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
      sock.connect(("8.8.8.8", 80))
      return f"http://{sock.getsockname()[0]}:{AP_VISUALIZER_PORT}"
  except OSError:
    return ""


class DeveloperLayoutMici(NavScroller):
  def __init__(self):
    super().__init__()
    self._ssh_fetcher = SshKeyFetcher(ui_state.params)

    def github_username_callback(username: str):
      if username:
        self._ssh_keys_btn.set_value("Loading...")
        self._ssh_keys_btn.set_enabled(False)

        def on_response(error):
          self._ssh_keys_btn.set_enabled(True)
          if error is None:
            self._ssh_keys_btn.set_value(username)
          else:
            self._ssh_keys_btn.set_value("Not set")
            gui_app.push_widget(BigDialog("", error))

        self._ssh_fetcher.fetch(username, on_response)
      else:
        self._ssh_fetcher.clear()
        self._ssh_keys_btn.set_value("Not set")

    def ssh_keys_callback():
      github_username = ui_state.params.get("GithubUsername") or ""
      dlg = BigInputDialog("enter GitHub username...", github_username, minimum_length=0, confirm_callback=github_username_callback)
      if not system_time_valid():
        dlg = BigDialog("", "Please connect to Wi-Fi to fetch your key.")
        gui_app.push_widget(dlg)
        return
      gui_app.push_widget(dlg)

    txt_ssh = gui_app.texture("icons_mici/settings/developer/ssh.png", 56, 64)
    github_username = ui_state.params.get("GithubUsername") or ""
    self._ssh_keys_btn = BigButton("SSH keys", "Not set" if not github_username else github_username, icon=txt_ssh)
    self._ssh_keys_btn.set_click_callback(ssh_keys_callback)

    # Branch switcher. The mici UI has no Software settings page, so the Target Branch selector
    # (present in the big tici/tizi UI) lives here as a pushed sub-page.
    self._branch_btn = BigButton("target branch", ui_state.params.get("UpdaterTargetBranch") or "", scroll=True)
    self._branch_btn.set_click_callback(self._open_branch_selector)

    # adb, ssh, ssh keys, debug mode, joystick debug mode, longitudinal maneuver mode, ip address
    # ******** Main Scroller ********
    self._adb_toggle = BigCircleParamControl(gui_app.texture("icons_mici/adb_short.png", 82, 82), "AdbEnabled", icon_offset=(0, 12))
    self._ssh_toggle = BigCircleParamControl(gui_app.texture("icons_mici/ssh_short.png", 82, 82), "SshEnabled", icon_offset=(0, 12))
    self._joystick_toggle = BigToggle("joystick debug mode",
                                      initial_state=ui_state.params.get_bool("JoystickDebugMode"),
                                      toggle_callback=self._on_joystick_debug_mode)
    self._long_maneuver_toggle = BigToggle("longitudinal maneuver mode",
                                           initial_state=ui_state.params.get_bool("LongitudinalManeuverMode"),
                                           toggle_callback=self._on_long_maneuver_mode)
    self._lat_maneuver_toggle = BigToggle("lateral maneuver mode",
                                          initial_state=ui_state.params.get_bool("LateralManeuverMode"),
                                          toggle_callback=self._on_lat_maneuver_mode)
    self._alpha_long_toggle = BigToggle("alpha longitudinal",
                                        initial_state=ui_state.params.get_bool("AlphaLongitudinalEnabled"),
                                        toggle_callback=self._on_alpha_long_enabled)
    self._rivian_no_harness_long_toggle = BigToggle("rivian no-harness long",
                                                    initial_state=ui_state.params.get_bool("RivianNoHarnessAlphaLong"),
                                                    toggle_callback=self._on_rivian_no_harness_long_enabled)
    self._debug_mode_toggle = BigParamControl("ui debug mode", "ShowDebugInfo",
                                              toggle_callback=lambda checked: (gui_app.set_show_touches(checked),
                                                                               gui_app.set_show_fps(checked)))
    # Rivian R1T steering tune profile (mici/comma-4 UI has no per-brand vehicle settings, so it
    # lives here). Auto picks by vehicle (Gen1 R1T -> aggressive, else tame); tame forces the
    # baseline. Read at car init, so the callback flags a restart to re-init and apply.
    self._rivian_tune_toggle = BigMultiParamToggle("steering tune", "RivianAggressiveTune",
                                                   ["auto", "tame"],
                                                   select_callback=self._on_rivian_tune)
    self._ap_visualizer_toggle = BigToggle("AP Visualizer", f"port {AP_VISUALIZER_PORT}",
                                           initial_state=ui_state.params.get_bool("APVisualizerEnabled"),
                                           toggle_callback=self._on_ap_visualizer_enabled)
    self._ap_visualizer_details_btn = BigButton("AP Visualizer details", "", scroll=True)
    self._ap_visualizer_details_btn.set_click_callback(self._open_ap_visualizer_details)
    self._update_ap_visualizer_value()

    self._scroller.add_widgets([
      self._adb_toggle,
      self._ssh_toggle,
      self._ssh_keys_btn,
      self._branch_btn,
      self._joystick_toggle,
      self._long_maneuver_toggle,
      self._lat_maneuver_toggle,
      self._rivian_no_harness_long_toggle,
      self._alpha_long_toggle,
      self._debug_mode_toggle,
      self._rivian_tune_toggle,
      self._ap_visualizer_toggle,
      self._ap_visualizer_details_btn,
    ])

    # Toggle lists
    self._refresh_toggles = (
      ("AdbEnabled", self._adb_toggle),
      ("SshEnabled", self._ssh_toggle),
      ("JoystickDebugMode", self._joystick_toggle),
      ("LongitudinalManeuverMode", self._long_maneuver_toggle),
      ("LateralManeuverMode", self._lat_maneuver_toggle),
      ("RivianNoHarnessAlphaLong", self._rivian_no_harness_long_toggle),
      ("AlphaLongitudinalEnabled", self._alpha_long_toggle),
      ("ShowDebugInfo", self._debug_mode_toggle),
      ("APVisualizerEnabled", self._ap_visualizer_toggle),
    )
    # NOTE: _rivian_tune_toggle is a BigMultiParamToggle (manages its own int param), so it's not in
    # _refresh_toggles (that loop does set_checked/get_bool, which is boolean-only).
    onroad_blocked_toggles = (self._adb_toggle, self._joystick_toggle)
    release_blocked_toggles = (self._joystick_toggle, self._long_maneuver_toggle, self._lat_maneuver_toggle,
                               self._rivian_no_harness_long_toggle, self._alpha_long_toggle)
    engaged_blocked_toggles = (self._long_maneuver_toggle, self._lat_maneuver_toggle,
                               self._rivian_no_harness_long_toggle, self._alpha_long_toggle, self._rivian_tune_toggle)

    # Hide non-release toggles on release builds
    for item in release_blocked_toggles:
      item.set_visible(not ui_state.is_release)

    # Disable toggles that require offroad
    for item in onroad_blocked_toggles:
      item.set_enabled(lambda: ui_state.is_offroad())

    # Disable toggles that require not engaged
    for item in engaged_blocked_toggles:
      item.set_enabled(lambda: not ui_state.engaged)

    # Set initial state
    if ui_state.params.get_bool("ShowDebugInfo"):
      gui_app.set_show_touches(True)
      gui_app.set_show_fps(True)

    ui_state.add_offroad_transition_callback(self._update_toggles)

  def _update_state(self):
    super()._update_state()
    self._ssh_fetcher.update()

    # Mirror the current target branch every frame so the row reflects a selection made in the
    # branch selector sub-page (which only writes the param) once we pop back here.
    target = ui_state.params.get("UpdaterTargetBranch") or ""
    if self._branch_btn.get_value() != target:
      self._branch_btn.set_value(target)
    self._update_ap_visualizer_value()

  def show_event(self):
    super().show_event()
    self._update_toggles()

  def _update_toggles(self):
    ui_state.update_params()

    # CP gating
    if ui_state.CP is not None:
      alpha_avail = ui_state.CP.alphaLongitudinalAvailable
      self._rivian_no_harness_long_toggle.set_visible(self._rivian_no_harness_long_available() and not ui_state.is_release)
      if not alpha_avail or ui_state.is_release:
        self._alpha_long_toggle.set_visible(False)
        ui_state.params.remove("AlphaLongitudinalEnabled")
      else:
        self._alpha_long_toggle.set_visible(True)

      long_man_enabled = ui_state.has_longitudinal_control and ui_state.is_offroad()
      self._long_maneuver_toggle.set_enabled(long_man_enabled)
      if not long_man_enabled:
        self._long_maneuver_toggle.set_checked(False)
        ui_state.params.put_bool("LongitudinalManeuverMode", False)

      lat_man_enabled = ui_state.is_offroad()
      self._lat_maneuver_toggle.set_enabled(lat_man_enabled)
    else:
      self._long_maneuver_toggle.set_enabled(False)
      self._lat_maneuver_toggle.set_enabled(False)
      self._rivian_no_harness_long_toggle.set_visible(False)
      self._alpha_long_toggle.set_visible(False)

    # Refresh toggles from params to mirror external changes
    for key, item in self._refresh_toggles:
      item.set_checked(ui_state.params.get_bool(key))

  def _open_branch_selector(self):
    gui_app.push_widget(BranchSelectorMici(back_callback=gui_app.pop_widget))

  def _update_ap_visualizer_value(self):
    enabled = ui_state.params.get_bool("APVisualizerEnabled")
    install_state = "ready" if ap_visualizer_installed() else "missing repo"
    self._ap_visualizer_details_btn.set_value(f"{'on' if enabled else 'off'}, {install_state}")

  def _open_ap_visualizer_details(self):
    fallback = ap_visualizer_fallback_url()
    status = "enabled" if ui_state.params.get_bool("APVisualizerEnabled") else "disabled"
    install_state = "ready" if ap_visualizer_installed() else "missing ap_visualizer_repo"
    details = f"{status}, {install_state}\n{AP_VISUALIZER_URL}\n"
    if fallback:
      details += f"{fallback}\n"
    details += f"QR: {AP_VISUALIZER_URL}/qr.svg"
    gui_app.push_widget(BigDialog("AP Visualizer", details))

  def _on_ap_visualizer_enabled(self, state: bool):
    ui_state.params.put_bool("APVisualizerEnabled", state)
    self._update_ap_visualizer_value()

  def _on_joystick_debug_mode(self, state: bool):
    ui_state.params.put_bool("JoystickDebugMode", state)
    ui_state.params.put_bool("LongitudinalManeuverMode", False)
    self._long_maneuver_toggle.set_checked(False)
    ui_state.params.put_bool("LateralManeuverMode", False)
    self._lat_maneuver_toggle.set_checked(False)

  def _on_long_maneuver_mode(self, state: bool):
    ui_state.params.put_bool("LongitudinalManeuverMode", state)
    ui_state.params.put_bool("JoystickDebugMode", False)
    self._joystick_toggle.set_checked(False)
    ui_state.params.put_bool("LateralManeuverMode", False)
    self._lat_maneuver_toggle.set_checked(False)
    restart_needed_callback(state)

  def _on_lat_maneuver_mode(self, state: bool):
    ui_state.params.put_bool("LateralManeuverMode", state)
    ui_state.params.put_bool("ExperimentalMode", False)
    ui_state.params.put_bool("JoystickDebugMode", False)
    self._joystick_toggle.set_checked(False)
    ui_state.params.put_bool("LongitudinalManeuverMode", False)
    self._long_maneuver_toggle.set_checked(False)
    restart_needed_callback(state)

  def _on_alpha_long_enabled(self, state: bool):
    # TODO: show confirmation dialog before enabling
    ui_state.params.put_bool("AlphaLongitudinalEnabled", state)
    restart_needed_callback(state)
    self._update_toggles()

  def _on_rivian_no_harness_long_enabled(self, state: bool):
    ui_state.params.put_bool("RivianNoHarnessAlphaLong", state)
    ui_state.params.put_bool("AlphaLongitudinalEnabled", False)
    ui_state.params.put_bool("ExperimentalMode", False)
    self._alpha_long_toggle.set_checked(False)
    restart_needed_callback(True)
    self._update_toggles()

  def _on_rivian_tune(self, value: str):
    # The widget writes the param itself (int index 0=auto/1=tame). Any tune change
    # needs a car re-init to take effect, so always flag a restart.
    restart_needed_callback(True)

  def _rivian_no_harness_long_available(self) -> bool:
    if ui_state.CP is None or ui_state.CP_SP is None:
      return False
    if ui_state.CP.brand != "rivian" or ui_state.CP.flags & RivianFlags.GEN2.value:
      return False
    return not bool(ui_state.CP_SP.flags & RivianFlagsSP.LONGITUDINAL_HARNESS_UPGRADE.value)
