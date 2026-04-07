#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_7855446520265556265);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5153870392277761757);
void car_H_mod_fun(double *state, double *out_5386268477849227143);
void car_f_fun(double *state, double dt, double *out_7894184285833143910);
void car_F_fun(double *state, double dt, double *out_8516340062973024620);
void car_h_25(double *state, double *unused, double *out_3227559797687982614);
void car_H_25(double *state, double *unused, double *out_482576652664562303);
void car_h_24(double *state, double *unused, double *out_6391073806329219193);
void car_H_24(double *state, double *unused, double *out_6092995153926955798);
void car_h_30(double *state, double *unused, double *out_3828977955301346168);
void car_H_30(double *state, double *unused, double *out_6434113688827054452);
void car_h_26(double *state, double *unused, double *out_9054885171136671115);
void car_H_26(double *state, double *unused, double *out_4224079971538618527);
void car_h_27(double *state, double *unused, double *out_1774113469972863031);
void car_H_27(double *state, double *unused, double *out_4259350377026629541);
void car_h_29(double *state, double *unused, double *out_2049307532257368920);
void car_H_29(double *state, double *unused, double *out_2545987650157078508);
void car_h_28(double *state, double *unused, double *out_830291850835834620);
void car_H_28(double *state, double *unused, double *out_2536411366912452066);
void car_h_31(double *state, double *unused, double *out_1776928405059099447);
void car_H_31(double *state, double *unused, double *out_451930690787601875);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}