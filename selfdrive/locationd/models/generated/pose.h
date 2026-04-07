#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1509083267251830649);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1626315071309903362);
void pose_H_mod_fun(double *state, double *out_5555600205584185478);
void pose_f_fun(double *state, double dt, double *out_1834893773028494468);
void pose_F_fun(double *state, double dt, double *out_4821520291802949801);
void pose_h_4(double *state, double *unused, double *out_844880312854774316);
void pose_H_4(double *state, double *unused, double *out_3388761460473635864);
void pose_h_10(double *state, double *unused, double *out_2440718403493438730);
void pose_H_10(double *state, double *unused, double *out_300556735062169610);
void pose_h_13(double *state, double *unused, double *out_3091723421696896469);
void pose_H_13(double *state, double *unused, double *out_176487635141303063);
void pose_h_14(double *state, double *unused, double *out_9069388618255276242);
void pose_H_14(double *state, double *unused, double *out_574479395865848665);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}