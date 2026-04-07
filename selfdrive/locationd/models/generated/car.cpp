#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_1216758841384990133) {
   out_1216758841384990133[0] = delta_x[0] + nom_x[0];
   out_1216758841384990133[1] = delta_x[1] + nom_x[1];
   out_1216758841384990133[2] = delta_x[2] + nom_x[2];
   out_1216758841384990133[3] = delta_x[3] + nom_x[3];
   out_1216758841384990133[4] = delta_x[4] + nom_x[4];
   out_1216758841384990133[5] = delta_x[5] + nom_x[5];
   out_1216758841384990133[6] = delta_x[6] + nom_x[6];
   out_1216758841384990133[7] = delta_x[7] + nom_x[7];
   out_1216758841384990133[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1190768490146126368) {
   out_1190768490146126368[0] = -nom_x[0] + true_x[0];
   out_1190768490146126368[1] = -nom_x[1] + true_x[1];
   out_1190768490146126368[2] = -nom_x[2] + true_x[2];
   out_1190768490146126368[3] = -nom_x[3] + true_x[3];
   out_1190768490146126368[4] = -nom_x[4] + true_x[4];
   out_1190768490146126368[5] = -nom_x[5] + true_x[5];
   out_1190768490146126368[6] = -nom_x[6] + true_x[6];
   out_1190768490146126368[7] = -nom_x[7] + true_x[7];
   out_1190768490146126368[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8617924790541324684) {
   out_8617924790541324684[0] = 1.0;
   out_8617924790541324684[1] = 0.0;
   out_8617924790541324684[2] = 0.0;
   out_8617924790541324684[3] = 0.0;
   out_8617924790541324684[4] = 0.0;
   out_8617924790541324684[5] = 0.0;
   out_8617924790541324684[6] = 0.0;
   out_8617924790541324684[7] = 0.0;
   out_8617924790541324684[8] = 0.0;
   out_8617924790541324684[9] = 0.0;
   out_8617924790541324684[10] = 1.0;
   out_8617924790541324684[11] = 0.0;
   out_8617924790541324684[12] = 0.0;
   out_8617924790541324684[13] = 0.0;
   out_8617924790541324684[14] = 0.0;
   out_8617924790541324684[15] = 0.0;
   out_8617924790541324684[16] = 0.0;
   out_8617924790541324684[17] = 0.0;
   out_8617924790541324684[18] = 0.0;
   out_8617924790541324684[19] = 0.0;
   out_8617924790541324684[20] = 1.0;
   out_8617924790541324684[21] = 0.0;
   out_8617924790541324684[22] = 0.0;
   out_8617924790541324684[23] = 0.0;
   out_8617924790541324684[24] = 0.0;
   out_8617924790541324684[25] = 0.0;
   out_8617924790541324684[26] = 0.0;
   out_8617924790541324684[27] = 0.0;
   out_8617924790541324684[28] = 0.0;
   out_8617924790541324684[29] = 0.0;
   out_8617924790541324684[30] = 1.0;
   out_8617924790541324684[31] = 0.0;
   out_8617924790541324684[32] = 0.0;
   out_8617924790541324684[33] = 0.0;
   out_8617924790541324684[34] = 0.0;
   out_8617924790541324684[35] = 0.0;
   out_8617924790541324684[36] = 0.0;
   out_8617924790541324684[37] = 0.0;
   out_8617924790541324684[38] = 0.0;
   out_8617924790541324684[39] = 0.0;
   out_8617924790541324684[40] = 1.0;
   out_8617924790541324684[41] = 0.0;
   out_8617924790541324684[42] = 0.0;
   out_8617924790541324684[43] = 0.0;
   out_8617924790541324684[44] = 0.0;
   out_8617924790541324684[45] = 0.0;
   out_8617924790541324684[46] = 0.0;
   out_8617924790541324684[47] = 0.0;
   out_8617924790541324684[48] = 0.0;
   out_8617924790541324684[49] = 0.0;
   out_8617924790541324684[50] = 1.0;
   out_8617924790541324684[51] = 0.0;
   out_8617924790541324684[52] = 0.0;
   out_8617924790541324684[53] = 0.0;
   out_8617924790541324684[54] = 0.0;
   out_8617924790541324684[55] = 0.0;
   out_8617924790541324684[56] = 0.0;
   out_8617924790541324684[57] = 0.0;
   out_8617924790541324684[58] = 0.0;
   out_8617924790541324684[59] = 0.0;
   out_8617924790541324684[60] = 1.0;
   out_8617924790541324684[61] = 0.0;
   out_8617924790541324684[62] = 0.0;
   out_8617924790541324684[63] = 0.0;
   out_8617924790541324684[64] = 0.0;
   out_8617924790541324684[65] = 0.0;
   out_8617924790541324684[66] = 0.0;
   out_8617924790541324684[67] = 0.0;
   out_8617924790541324684[68] = 0.0;
   out_8617924790541324684[69] = 0.0;
   out_8617924790541324684[70] = 1.0;
   out_8617924790541324684[71] = 0.0;
   out_8617924790541324684[72] = 0.0;
   out_8617924790541324684[73] = 0.0;
   out_8617924790541324684[74] = 0.0;
   out_8617924790541324684[75] = 0.0;
   out_8617924790541324684[76] = 0.0;
   out_8617924790541324684[77] = 0.0;
   out_8617924790541324684[78] = 0.0;
   out_8617924790541324684[79] = 0.0;
   out_8617924790541324684[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4683014027413001684) {
   out_4683014027413001684[0] = state[0];
   out_4683014027413001684[1] = state[1];
   out_4683014027413001684[2] = state[2];
   out_4683014027413001684[3] = state[3];
   out_4683014027413001684[4] = state[4];
   out_4683014027413001684[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4683014027413001684[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4683014027413001684[7] = state[7];
   out_4683014027413001684[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3738720563522651303) {
   out_3738720563522651303[0] = 1;
   out_3738720563522651303[1] = 0;
   out_3738720563522651303[2] = 0;
   out_3738720563522651303[3] = 0;
   out_3738720563522651303[4] = 0;
   out_3738720563522651303[5] = 0;
   out_3738720563522651303[6] = 0;
   out_3738720563522651303[7] = 0;
   out_3738720563522651303[8] = 0;
   out_3738720563522651303[9] = 0;
   out_3738720563522651303[10] = 1;
   out_3738720563522651303[11] = 0;
   out_3738720563522651303[12] = 0;
   out_3738720563522651303[13] = 0;
   out_3738720563522651303[14] = 0;
   out_3738720563522651303[15] = 0;
   out_3738720563522651303[16] = 0;
   out_3738720563522651303[17] = 0;
   out_3738720563522651303[18] = 0;
   out_3738720563522651303[19] = 0;
   out_3738720563522651303[20] = 1;
   out_3738720563522651303[21] = 0;
   out_3738720563522651303[22] = 0;
   out_3738720563522651303[23] = 0;
   out_3738720563522651303[24] = 0;
   out_3738720563522651303[25] = 0;
   out_3738720563522651303[26] = 0;
   out_3738720563522651303[27] = 0;
   out_3738720563522651303[28] = 0;
   out_3738720563522651303[29] = 0;
   out_3738720563522651303[30] = 1;
   out_3738720563522651303[31] = 0;
   out_3738720563522651303[32] = 0;
   out_3738720563522651303[33] = 0;
   out_3738720563522651303[34] = 0;
   out_3738720563522651303[35] = 0;
   out_3738720563522651303[36] = 0;
   out_3738720563522651303[37] = 0;
   out_3738720563522651303[38] = 0;
   out_3738720563522651303[39] = 0;
   out_3738720563522651303[40] = 1;
   out_3738720563522651303[41] = 0;
   out_3738720563522651303[42] = 0;
   out_3738720563522651303[43] = 0;
   out_3738720563522651303[44] = 0;
   out_3738720563522651303[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3738720563522651303[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3738720563522651303[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3738720563522651303[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3738720563522651303[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3738720563522651303[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3738720563522651303[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3738720563522651303[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3738720563522651303[53] = -9.8100000000000005*dt;
   out_3738720563522651303[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3738720563522651303[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3738720563522651303[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3738720563522651303[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3738720563522651303[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3738720563522651303[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3738720563522651303[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3738720563522651303[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3738720563522651303[62] = 0;
   out_3738720563522651303[63] = 0;
   out_3738720563522651303[64] = 0;
   out_3738720563522651303[65] = 0;
   out_3738720563522651303[66] = 0;
   out_3738720563522651303[67] = 0;
   out_3738720563522651303[68] = 0;
   out_3738720563522651303[69] = 0;
   out_3738720563522651303[70] = 1;
   out_3738720563522651303[71] = 0;
   out_3738720563522651303[72] = 0;
   out_3738720563522651303[73] = 0;
   out_3738720563522651303[74] = 0;
   out_3738720563522651303[75] = 0;
   out_3738720563522651303[76] = 0;
   out_3738720563522651303[77] = 0;
   out_3738720563522651303[78] = 0;
   out_3738720563522651303[79] = 0;
   out_3738720563522651303[80] = 1;
}
void h_25(double *state, double *unused, double *out_4535154382052686003) {
   out_4535154382052686003[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3714232965356659844) {
   out_3714232965356659844[0] = 0;
   out_3714232965356659844[1] = 0;
   out_3714232965356659844[2] = 0;
   out_3714232965356659844[3] = 0;
   out_3714232965356659844[4] = 0;
   out_3714232965356659844[5] = 0;
   out_3714232965356659844[6] = 1;
   out_3714232965356659844[7] = 0;
   out_3714232965356659844[8] = 0;
}
void h_24(double *state, double *unused, double *out_2741591425358361650) {
   out_2741591425358361650[0] = state[4];
   out_2741591425358361650[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2861338841234858257) {
   out_2861338841234858257[0] = 0;
   out_2861338841234858257[1] = 0;
   out_2861338841234858257[2] = 0;
   out_2861338841234858257[3] = 0;
   out_2861338841234858257[4] = 1;
   out_2861338841234858257[5] = 0;
   out_2861338841234858257[6] = 0;
   out_2861338841234858257[7] = 0;
   out_2861338841234858257[8] = 0;
   out_2861338841234858257[9] = 0;
   out_2861338841234858257[10] = 0;
   out_2861338841234858257[11] = 0;
   out_2861338841234858257[12] = 0;
   out_2861338841234858257[13] = 0;
   out_2861338841234858257[14] = 1;
   out_2861338841234858257[15] = 0;
   out_2861338841234858257[16] = 0;
   out_2861338841234858257[17] = 0;
}
void h_30(double *state, double *unused, double *out_5937118840203142971) {
   out_5937118840203142971[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1195900006849411217) {
   out_1195900006849411217[0] = 0;
   out_1195900006849411217[1] = 0;
   out_1195900006849411217[2] = 0;
   out_1195900006849411217[3] = 0;
   out_1195900006849411217[4] = 1;
   out_1195900006849411217[5] = 0;
   out_1195900006849411217[6] = 0;
   out_1195900006849411217[7] = 0;
   out_1195900006849411217[8] = 0;
}
void h_26(double *state, double *unused, double *out_3791788313637716319) {
   out_3791788313637716319[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7455736284230716068) {
   out_7455736284230716068[0] = 0;
   out_7455736284230716068[1] = 0;
   out_7455736284230716068[2] = 0;
   out_7455736284230716068[3] = 0;
   out_7455736284230716068[4] = 0;
   out_7455736284230716068[5] = 0;
   out_7455736284230716068[6] = 0;
   out_7455736284230716068[7] = 1;
   out_7455736284230716068[8] = 0;
}
void h_27(double *state, double *unused, double *out_7704431904176244558) {
   out_7704431904176244558[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1027694064334532000) {
   out_1027694064334532000[0] = 0;
   out_1027694064334532000[1] = 0;
   out_1027694064334532000[2] = 0;
   out_1027694064334532000[3] = 1;
   out_1027694064334532000[4] = 0;
   out_1027694064334532000[5] = 0;
   out_1027694064334532000[6] = 0;
   out_1027694064334532000[7] = 0;
   out_1027694064334532000[8] = 0;
}
void h_29(double *state, double *unused, double *out_935445572542297326) {
   out_935445572542297326[0] = state[1];
}
void H_29(double *state, double *unused, double *out_685668662535019033) {
   out_685668662535019033[0] = 0;
   out_685668662535019033[1] = 1;
   out_685668662535019033[2] = 0;
   out_685668662535019033[3] = 0;
   out_685668662535019033[4] = 0;
   out_685668662535019033[5] = 0;
   out_685668662535019033[6] = 0;
   out_685668662535019033[7] = 0;
   out_685668662535019033[8] = 0;
}
void h_28(double *state, double *unused, double *out_2154149487728465650) {
   out_2154149487728465650[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5768067679604549607) {
   out_5768067679604549607[0] = 1;
   out_5768067679604549607[1] = 0;
   out_5768067679604549607[2] = 0;
   out_5768067679604549607[3] = 0;
   out_5768067679604549607[4] = 0;
   out_5768067679604549607[5] = 0;
   out_5768067679604549607[6] = 0;
   out_5768067679604549607[7] = 0;
   out_5768067679604549607[8] = 0;
}
void h_31(double *state, double *unused, double *out_8596981642967880406) {
   out_8596981642967880406[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3683587003479699416) {
   out_3683587003479699416[0] = 0;
   out_3683587003479699416[1] = 0;
   out_3683587003479699416[2] = 0;
   out_3683587003479699416[3] = 0;
   out_3683587003479699416[4] = 0;
   out_3683587003479699416[5] = 0;
   out_3683587003479699416[6] = 0;
   out_3683587003479699416[7] = 0;
   out_3683587003479699416[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_1216758841384990133) {
  err_fun(nom_x, delta_x, out_1216758841384990133);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1190768490146126368) {
  inv_err_fun(nom_x, true_x, out_1190768490146126368);
}
void car_H_mod_fun(double *state, double *out_8617924790541324684) {
  H_mod_fun(state, out_8617924790541324684);
}
void car_f_fun(double *state, double dt, double *out_4683014027413001684) {
  f_fun(state,  dt, out_4683014027413001684);
}
void car_F_fun(double *state, double dt, double *out_3738720563522651303) {
  F_fun(state,  dt, out_3738720563522651303);
}
void car_h_25(double *state, double *unused, double *out_4535154382052686003) {
  h_25(state, unused, out_4535154382052686003);
}
void car_H_25(double *state, double *unused, double *out_3714232965356659844) {
  H_25(state, unused, out_3714232965356659844);
}
void car_h_24(double *state, double *unused, double *out_2741591425358361650) {
  h_24(state, unused, out_2741591425358361650);
}
void car_H_24(double *state, double *unused, double *out_2861338841234858257) {
  H_24(state, unused, out_2861338841234858257);
}
void car_h_30(double *state, double *unused, double *out_5937118840203142971) {
  h_30(state, unused, out_5937118840203142971);
}
void car_H_30(double *state, double *unused, double *out_1195900006849411217) {
  H_30(state, unused, out_1195900006849411217);
}
void car_h_26(double *state, double *unused, double *out_3791788313637716319) {
  h_26(state, unused, out_3791788313637716319);
}
void car_H_26(double *state, double *unused, double *out_7455736284230716068) {
  H_26(state, unused, out_7455736284230716068);
}
void car_h_27(double *state, double *unused, double *out_7704431904176244558) {
  h_27(state, unused, out_7704431904176244558);
}
void car_H_27(double *state, double *unused, double *out_1027694064334532000) {
  H_27(state, unused, out_1027694064334532000);
}
void car_h_29(double *state, double *unused, double *out_935445572542297326) {
  h_29(state, unused, out_935445572542297326);
}
void car_H_29(double *state, double *unused, double *out_685668662535019033) {
  H_29(state, unused, out_685668662535019033);
}
void car_h_28(double *state, double *unused, double *out_2154149487728465650) {
  h_28(state, unused, out_2154149487728465650);
}
void car_H_28(double *state, double *unused, double *out_5768067679604549607) {
  H_28(state, unused, out_5768067679604549607);
}
void car_h_31(double *state, double *unused, double *out_8596981642967880406) {
  h_31(state, unused, out_8596981642967880406);
}
void car_H_31(double *state, double *unused, double *out_3683587003479699416) {
  H_31(state, unused, out_3683587003479699416);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
