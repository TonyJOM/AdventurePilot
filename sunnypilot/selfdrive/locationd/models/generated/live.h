#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_4916403888537873074);
void live_err_fun(double *nom_x, double *delta_x, double *out_4616539082276106612);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_5565283859415893331);
void live_H_mod_fun(double *state, double *out_6491739185076789039);
void live_f_fun(double *state, double dt, double *out_6694514971425039147);
void live_F_fun(double *state, double dt, double *out_6298718628107445955);
void live_h_4(double *state, double *unused, double *out_7371819729515111633);
void live_H_4(double *state, double *unused, double *out_3975576613932313089);
void live_h_9(double *state, double *unused, double *out_4017767985073763009);
void live_H_9(double *state, double *unused, double *out_7183948524512791057);
void live_h_10(double *state, double *unused, double *out_7104599524437582537);
void live_H_10(double *state, double *unused, double *out_1735408632610833668);
void live_h_12(double *state, double *unused, double *out_7251444119446208301);
void live_H_12(double *state, double *unused, double *out_4596675638979906756);
void live_h_35(double *state, double *unused, double *out_2801182256603003531);
void live_H_35(double *state, double *unused, double *out_7342238671304920465);
void live_h_32(double *state, double *unused, double *out_2293566090903448056);
void live_H_32(double *state, double *unused, double *out_8399480889502881214);
void live_h_13(double *state, double *unused, double *out_7547359871020749631);
void live_H_13(double *state, double *unused, double *out_3645122438323830331);
void live_h_14(double *state, double *unused, double *out_4017767985073763009);
void live_H_14(double *state, double *unused, double *out_7183948524512791057);
void live_h_33(double *state, double *unused, double *out_7750415600216692881);
void live_H_33(double *state, double *unused, double *out_7953948397765773547);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}