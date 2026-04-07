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
void err_fun(double *nom_x, double *delta_x, double *out_7855446520265556265) {
   out_7855446520265556265[0] = delta_x[0] + nom_x[0];
   out_7855446520265556265[1] = delta_x[1] + nom_x[1];
   out_7855446520265556265[2] = delta_x[2] + nom_x[2];
   out_7855446520265556265[3] = delta_x[3] + nom_x[3];
   out_7855446520265556265[4] = delta_x[4] + nom_x[4];
   out_7855446520265556265[5] = delta_x[5] + nom_x[5];
   out_7855446520265556265[6] = delta_x[6] + nom_x[6];
   out_7855446520265556265[7] = delta_x[7] + nom_x[7];
   out_7855446520265556265[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5153870392277761757) {
   out_5153870392277761757[0] = -nom_x[0] + true_x[0];
   out_5153870392277761757[1] = -nom_x[1] + true_x[1];
   out_5153870392277761757[2] = -nom_x[2] + true_x[2];
   out_5153870392277761757[3] = -nom_x[3] + true_x[3];
   out_5153870392277761757[4] = -nom_x[4] + true_x[4];
   out_5153870392277761757[5] = -nom_x[5] + true_x[5];
   out_5153870392277761757[6] = -nom_x[6] + true_x[6];
   out_5153870392277761757[7] = -nom_x[7] + true_x[7];
   out_5153870392277761757[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5386268477849227143) {
   out_5386268477849227143[0] = 1.0;
   out_5386268477849227143[1] = 0.0;
   out_5386268477849227143[2] = 0.0;
   out_5386268477849227143[3] = 0.0;
   out_5386268477849227143[4] = 0.0;
   out_5386268477849227143[5] = 0.0;
   out_5386268477849227143[6] = 0.0;
   out_5386268477849227143[7] = 0.0;
   out_5386268477849227143[8] = 0.0;
   out_5386268477849227143[9] = 0.0;
   out_5386268477849227143[10] = 1.0;
   out_5386268477849227143[11] = 0.0;
   out_5386268477849227143[12] = 0.0;
   out_5386268477849227143[13] = 0.0;
   out_5386268477849227143[14] = 0.0;
   out_5386268477849227143[15] = 0.0;
   out_5386268477849227143[16] = 0.0;
   out_5386268477849227143[17] = 0.0;
   out_5386268477849227143[18] = 0.0;
   out_5386268477849227143[19] = 0.0;
   out_5386268477849227143[20] = 1.0;
   out_5386268477849227143[21] = 0.0;
   out_5386268477849227143[22] = 0.0;
   out_5386268477849227143[23] = 0.0;
   out_5386268477849227143[24] = 0.0;
   out_5386268477849227143[25] = 0.0;
   out_5386268477849227143[26] = 0.0;
   out_5386268477849227143[27] = 0.0;
   out_5386268477849227143[28] = 0.0;
   out_5386268477849227143[29] = 0.0;
   out_5386268477849227143[30] = 1.0;
   out_5386268477849227143[31] = 0.0;
   out_5386268477849227143[32] = 0.0;
   out_5386268477849227143[33] = 0.0;
   out_5386268477849227143[34] = 0.0;
   out_5386268477849227143[35] = 0.0;
   out_5386268477849227143[36] = 0.0;
   out_5386268477849227143[37] = 0.0;
   out_5386268477849227143[38] = 0.0;
   out_5386268477849227143[39] = 0.0;
   out_5386268477849227143[40] = 1.0;
   out_5386268477849227143[41] = 0.0;
   out_5386268477849227143[42] = 0.0;
   out_5386268477849227143[43] = 0.0;
   out_5386268477849227143[44] = 0.0;
   out_5386268477849227143[45] = 0.0;
   out_5386268477849227143[46] = 0.0;
   out_5386268477849227143[47] = 0.0;
   out_5386268477849227143[48] = 0.0;
   out_5386268477849227143[49] = 0.0;
   out_5386268477849227143[50] = 1.0;
   out_5386268477849227143[51] = 0.0;
   out_5386268477849227143[52] = 0.0;
   out_5386268477849227143[53] = 0.0;
   out_5386268477849227143[54] = 0.0;
   out_5386268477849227143[55] = 0.0;
   out_5386268477849227143[56] = 0.0;
   out_5386268477849227143[57] = 0.0;
   out_5386268477849227143[58] = 0.0;
   out_5386268477849227143[59] = 0.0;
   out_5386268477849227143[60] = 1.0;
   out_5386268477849227143[61] = 0.0;
   out_5386268477849227143[62] = 0.0;
   out_5386268477849227143[63] = 0.0;
   out_5386268477849227143[64] = 0.0;
   out_5386268477849227143[65] = 0.0;
   out_5386268477849227143[66] = 0.0;
   out_5386268477849227143[67] = 0.0;
   out_5386268477849227143[68] = 0.0;
   out_5386268477849227143[69] = 0.0;
   out_5386268477849227143[70] = 1.0;
   out_5386268477849227143[71] = 0.0;
   out_5386268477849227143[72] = 0.0;
   out_5386268477849227143[73] = 0.0;
   out_5386268477849227143[74] = 0.0;
   out_5386268477849227143[75] = 0.0;
   out_5386268477849227143[76] = 0.0;
   out_5386268477849227143[77] = 0.0;
   out_5386268477849227143[78] = 0.0;
   out_5386268477849227143[79] = 0.0;
   out_5386268477849227143[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7894184285833143910) {
   out_7894184285833143910[0] = state[0];
   out_7894184285833143910[1] = state[1];
   out_7894184285833143910[2] = state[2];
   out_7894184285833143910[3] = state[3];
   out_7894184285833143910[4] = state[4];
   out_7894184285833143910[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7894184285833143910[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7894184285833143910[7] = state[7];
   out_7894184285833143910[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8516340062973024620) {
   out_8516340062973024620[0] = 1;
   out_8516340062973024620[1] = 0;
   out_8516340062973024620[2] = 0;
   out_8516340062973024620[3] = 0;
   out_8516340062973024620[4] = 0;
   out_8516340062973024620[5] = 0;
   out_8516340062973024620[6] = 0;
   out_8516340062973024620[7] = 0;
   out_8516340062973024620[8] = 0;
   out_8516340062973024620[9] = 0;
   out_8516340062973024620[10] = 1;
   out_8516340062973024620[11] = 0;
   out_8516340062973024620[12] = 0;
   out_8516340062973024620[13] = 0;
   out_8516340062973024620[14] = 0;
   out_8516340062973024620[15] = 0;
   out_8516340062973024620[16] = 0;
   out_8516340062973024620[17] = 0;
   out_8516340062973024620[18] = 0;
   out_8516340062973024620[19] = 0;
   out_8516340062973024620[20] = 1;
   out_8516340062973024620[21] = 0;
   out_8516340062973024620[22] = 0;
   out_8516340062973024620[23] = 0;
   out_8516340062973024620[24] = 0;
   out_8516340062973024620[25] = 0;
   out_8516340062973024620[26] = 0;
   out_8516340062973024620[27] = 0;
   out_8516340062973024620[28] = 0;
   out_8516340062973024620[29] = 0;
   out_8516340062973024620[30] = 1;
   out_8516340062973024620[31] = 0;
   out_8516340062973024620[32] = 0;
   out_8516340062973024620[33] = 0;
   out_8516340062973024620[34] = 0;
   out_8516340062973024620[35] = 0;
   out_8516340062973024620[36] = 0;
   out_8516340062973024620[37] = 0;
   out_8516340062973024620[38] = 0;
   out_8516340062973024620[39] = 0;
   out_8516340062973024620[40] = 1;
   out_8516340062973024620[41] = 0;
   out_8516340062973024620[42] = 0;
   out_8516340062973024620[43] = 0;
   out_8516340062973024620[44] = 0;
   out_8516340062973024620[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8516340062973024620[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8516340062973024620[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8516340062973024620[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8516340062973024620[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8516340062973024620[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8516340062973024620[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8516340062973024620[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8516340062973024620[53] = -9.8100000000000005*dt;
   out_8516340062973024620[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8516340062973024620[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8516340062973024620[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8516340062973024620[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8516340062973024620[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8516340062973024620[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8516340062973024620[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8516340062973024620[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8516340062973024620[62] = 0;
   out_8516340062973024620[63] = 0;
   out_8516340062973024620[64] = 0;
   out_8516340062973024620[65] = 0;
   out_8516340062973024620[66] = 0;
   out_8516340062973024620[67] = 0;
   out_8516340062973024620[68] = 0;
   out_8516340062973024620[69] = 0;
   out_8516340062973024620[70] = 1;
   out_8516340062973024620[71] = 0;
   out_8516340062973024620[72] = 0;
   out_8516340062973024620[73] = 0;
   out_8516340062973024620[74] = 0;
   out_8516340062973024620[75] = 0;
   out_8516340062973024620[76] = 0;
   out_8516340062973024620[77] = 0;
   out_8516340062973024620[78] = 0;
   out_8516340062973024620[79] = 0;
   out_8516340062973024620[80] = 1;
}
void h_25(double *state, double *unused, double *out_3227559797687982614) {
   out_3227559797687982614[0] = state[6];
}
void H_25(double *state, double *unused, double *out_482576652664562303) {
   out_482576652664562303[0] = 0;
   out_482576652664562303[1] = 0;
   out_482576652664562303[2] = 0;
   out_482576652664562303[3] = 0;
   out_482576652664562303[4] = 0;
   out_482576652664562303[5] = 0;
   out_482576652664562303[6] = 1;
   out_482576652664562303[7] = 0;
   out_482576652664562303[8] = 0;
}
void h_24(double *state, double *unused, double *out_6391073806329219193) {
   out_6391073806329219193[0] = state[4];
   out_6391073806329219193[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6092995153926955798) {
   out_6092995153926955798[0] = 0;
   out_6092995153926955798[1] = 0;
   out_6092995153926955798[2] = 0;
   out_6092995153926955798[3] = 0;
   out_6092995153926955798[4] = 1;
   out_6092995153926955798[5] = 0;
   out_6092995153926955798[6] = 0;
   out_6092995153926955798[7] = 0;
   out_6092995153926955798[8] = 0;
   out_6092995153926955798[9] = 0;
   out_6092995153926955798[10] = 0;
   out_6092995153926955798[11] = 0;
   out_6092995153926955798[12] = 0;
   out_6092995153926955798[13] = 0;
   out_6092995153926955798[14] = 1;
   out_6092995153926955798[15] = 0;
   out_6092995153926955798[16] = 0;
   out_6092995153926955798[17] = 0;
}
void h_30(double *state, double *unused, double *out_3828977955301346168) {
   out_3828977955301346168[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6434113688827054452) {
   out_6434113688827054452[0] = 0;
   out_6434113688827054452[1] = 0;
   out_6434113688827054452[2] = 0;
   out_6434113688827054452[3] = 0;
   out_6434113688827054452[4] = 1;
   out_6434113688827054452[5] = 0;
   out_6434113688827054452[6] = 0;
   out_6434113688827054452[7] = 0;
   out_6434113688827054452[8] = 0;
}
void h_26(double *state, double *unused, double *out_9054885171136671115) {
   out_9054885171136671115[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4224079971538618527) {
   out_4224079971538618527[0] = 0;
   out_4224079971538618527[1] = 0;
   out_4224079971538618527[2] = 0;
   out_4224079971538618527[3] = 0;
   out_4224079971538618527[4] = 0;
   out_4224079971538618527[5] = 0;
   out_4224079971538618527[6] = 0;
   out_4224079971538618527[7] = 1;
   out_4224079971538618527[8] = 0;
}
void h_27(double *state, double *unused, double *out_1774113469972863031) {
   out_1774113469972863031[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4259350377026629541) {
   out_4259350377026629541[0] = 0;
   out_4259350377026629541[1] = 0;
   out_4259350377026629541[2] = 0;
   out_4259350377026629541[3] = 1;
   out_4259350377026629541[4] = 0;
   out_4259350377026629541[5] = 0;
   out_4259350377026629541[6] = 0;
   out_4259350377026629541[7] = 0;
   out_4259350377026629541[8] = 0;
}
void h_29(double *state, double *unused, double *out_2049307532257368920) {
   out_2049307532257368920[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2545987650157078508) {
   out_2545987650157078508[0] = 0;
   out_2545987650157078508[1] = 1;
   out_2545987650157078508[2] = 0;
   out_2545987650157078508[3] = 0;
   out_2545987650157078508[4] = 0;
   out_2545987650157078508[5] = 0;
   out_2545987650157078508[6] = 0;
   out_2545987650157078508[7] = 0;
   out_2545987650157078508[8] = 0;
}
void h_28(double *state, double *unused, double *out_830291850835834620) {
   out_830291850835834620[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2536411366912452066) {
   out_2536411366912452066[0] = 1;
   out_2536411366912452066[1] = 0;
   out_2536411366912452066[2] = 0;
   out_2536411366912452066[3] = 0;
   out_2536411366912452066[4] = 0;
   out_2536411366912452066[5] = 0;
   out_2536411366912452066[6] = 0;
   out_2536411366912452066[7] = 0;
   out_2536411366912452066[8] = 0;
}
void h_31(double *state, double *unused, double *out_1776928405059099447) {
   out_1776928405059099447[0] = state[8];
}
void H_31(double *state, double *unused, double *out_451930690787601875) {
   out_451930690787601875[0] = 0;
   out_451930690787601875[1] = 0;
   out_451930690787601875[2] = 0;
   out_451930690787601875[3] = 0;
   out_451930690787601875[4] = 0;
   out_451930690787601875[5] = 0;
   out_451930690787601875[6] = 0;
   out_451930690787601875[7] = 0;
   out_451930690787601875[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7855446520265556265) {
  err_fun(nom_x, delta_x, out_7855446520265556265);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5153870392277761757) {
  inv_err_fun(nom_x, true_x, out_5153870392277761757);
}
void car_H_mod_fun(double *state, double *out_5386268477849227143) {
  H_mod_fun(state, out_5386268477849227143);
}
void car_f_fun(double *state, double dt, double *out_7894184285833143910) {
  f_fun(state,  dt, out_7894184285833143910);
}
void car_F_fun(double *state, double dt, double *out_8516340062973024620) {
  F_fun(state,  dt, out_8516340062973024620);
}
void car_h_25(double *state, double *unused, double *out_3227559797687982614) {
  h_25(state, unused, out_3227559797687982614);
}
void car_H_25(double *state, double *unused, double *out_482576652664562303) {
  H_25(state, unused, out_482576652664562303);
}
void car_h_24(double *state, double *unused, double *out_6391073806329219193) {
  h_24(state, unused, out_6391073806329219193);
}
void car_H_24(double *state, double *unused, double *out_6092995153926955798) {
  H_24(state, unused, out_6092995153926955798);
}
void car_h_30(double *state, double *unused, double *out_3828977955301346168) {
  h_30(state, unused, out_3828977955301346168);
}
void car_H_30(double *state, double *unused, double *out_6434113688827054452) {
  H_30(state, unused, out_6434113688827054452);
}
void car_h_26(double *state, double *unused, double *out_9054885171136671115) {
  h_26(state, unused, out_9054885171136671115);
}
void car_H_26(double *state, double *unused, double *out_4224079971538618527) {
  H_26(state, unused, out_4224079971538618527);
}
void car_h_27(double *state, double *unused, double *out_1774113469972863031) {
  h_27(state, unused, out_1774113469972863031);
}
void car_H_27(double *state, double *unused, double *out_4259350377026629541) {
  H_27(state, unused, out_4259350377026629541);
}
void car_h_29(double *state, double *unused, double *out_2049307532257368920) {
  h_29(state, unused, out_2049307532257368920);
}
void car_H_29(double *state, double *unused, double *out_2545987650157078508) {
  H_29(state, unused, out_2545987650157078508);
}
void car_h_28(double *state, double *unused, double *out_830291850835834620) {
  h_28(state, unused, out_830291850835834620);
}
void car_H_28(double *state, double *unused, double *out_2536411366912452066) {
  H_28(state, unused, out_2536411366912452066);
}
void car_h_31(double *state, double *unused, double *out_1776928405059099447) {
  h_31(state, unused, out_1776928405059099447);
}
void car_H_31(double *state, double *unused, double *out_451930690787601875) {
  H_31(state, unused, out_451930690787601875);
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
