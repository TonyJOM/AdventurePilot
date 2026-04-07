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
void car_err_fun(double *nom_x, double *delta_x, double *out_1216758841384990133);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1190768490146126368);
void car_H_mod_fun(double *state, double *out_8617924790541324684);
void car_f_fun(double *state, double dt, double *out_4683014027413001684);
void car_F_fun(double *state, double dt, double *out_3738720563522651303);
void car_h_25(double *state, double *unused, double *out_4535154382052686003);
void car_H_25(double *state, double *unused, double *out_3714232965356659844);
void car_h_24(double *state, double *unused, double *out_2741591425358361650);
void car_H_24(double *state, double *unused, double *out_2861338841234858257);
void car_h_30(double *state, double *unused, double *out_5937118840203142971);
void car_H_30(double *state, double *unused, double *out_1195900006849411217);
void car_h_26(double *state, double *unused, double *out_3791788313637716319);
void car_H_26(double *state, double *unused, double *out_7455736284230716068);
void car_h_27(double *state, double *unused, double *out_7704431904176244558);
void car_H_27(double *state, double *unused, double *out_1027694064334532000);
void car_h_29(double *state, double *unused, double *out_935445572542297326);
void car_H_29(double *state, double *unused, double *out_685668662535019033);
void car_h_28(double *state, double *unused, double *out_2154149487728465650);
void car_H_28(double *state, double *unused, double *out_5768067679604549607);
void car_h_31(double *state, double *unused, double *out_8596981642967880406);
void car_H_31(double *state, double *unused, double *out_3683587003479699416);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}