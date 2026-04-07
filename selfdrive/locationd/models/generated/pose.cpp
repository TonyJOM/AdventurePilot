#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_1509083267251830649) {
   out_1509083267251830649[0] = delta_x[0] + nom_x[0];
   out_1509083267251830649[1] = delta_x[1] + nom_x[1];
   out_1509083267251830649[2] = delta_x[2] + nom_x[2];
   out_1509083267251830649[3] = delta_x[3] + nom_x[3];
   out_1509083267251830649[4] = delta_x[4] + nom_x[4];
   out_1509083267251830649[5] = delta_x[5] + nom_x[5];
   out_1509083267251830649[6] = delta_x[6] + nom_x[6];
   out_1509083267251830649[7] = delta_x[7] + nom_x[7];
   out_1509083267251830649[8] = delta_x[8] + nom_x[8];
   out_1509083267251830649[9] = delta_x[9] + nom_x[9];
   out_1509083267251830649[10] = delta_x[10] + nom_x[10];
   out_1509083267251830649[11] = delta_x[11] + nom_x[11];
   out_1509083267251830649[12] = delta_x[12] + nom_x[12];
   out_1509083267251830649[13] = delta_x[13] + nom_x[13];
   out_1509083267251830649[14] = delta_x[14] + nom_x[14];
   out_1509083267251830649[15] = delta_x[15] + nom_x[15];
   out_1509083267251830649[16] = delta_x[16] + nom_x[16];
   out_1509083267251830649[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1626315071309903362) {
   out_1626315071309903362[0] = -nom_x[0] + true_x[0];
   out_1626315071309903362[1] = -nom_x[1] + true_x[1];
   out_1626315071309903362[2] = -nom_x[2] + true_x[2];
   out_1626315071309903362[3] = -nom_x[3] + true_x[3];
   out_1626315071309903362[4] = -nom_x[4] + true_x[4];
   out_1626315071309903362[5] = -nom_x[5] + true_x[5];
   out_1626315071309903362[6] = -nom_x[6] + true_x[6];
   out_1626315071309903362[7] = -nom_x[7] + true_x[7];
   out_1626315071309903362[8] = -nom_x[8] + true_x[8];
   out_1626315071309903362[9] = -nom_x[9] + true_x[9];
   out_1626315071309903362[10] = -nom_x[10] + true_x[10];
   out_1626315071309903362[11] = -nom_x[11] + true_x[11];
   out_1626315071309903362[12] = -nom_x[12] + true_x[12];
   out_1626315071309903362[13] = -nom_x[13] + true_x[13];
   out_1626315071309903362[14] = -nom_x[14] + true_x[14];
   out_1626315071309903362[15] = -nom_x[15] + true_x[15];
   out_1626315071309903362[16] = -nom_x[16] + true_x[16];
   out_1626315071309903362[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5555600205584185478) {
   out_5555600205584185478[0] = 1.0;
   out_5555600205584185478[1] = 0.0;
   out_5555600205584185478[2] = 0.0;
   out_5555600205584185478[3] = 0.0;
   out_5555600205584185478[4] = 0.0;
   out_5555600205584185478[5] = 0.0;
   out_5555600205584185478[6] = 0.0;
   out_5555600205584185478[7] = 0.0;
   out_5555600205584185478[8] = 0.0;
   out_5555600205584185478[9] = 0.0;
   out_5555600205584185478[10] = 0.0;
   out_5555600205584185478[11] = 0.0;
   out_5555600205584185478[12] = 0.0;
   out_5555600205584185478[13] = 0.0;
   out_5555600205584185478[14] = 0.0;
   out_5555600205584185478[15] = 0.0;
   out_5555600205584185478[16] = 0.0;
   out_5555600205584185478[17] = 0.0;
   out_5555600205584185478[18] = 0.0;
   out_5555600205584185478[19] = 1.0;
   out_5555600205584185478[20] = 0.0;
   out_5555600205584185478[21] = 0.0;
   out_5555600205584185478[22] = 0.0;
   out_5555600205584185478[23] = 0.0;
   out_5555600205584185478[24] = 0.0;
   out_5555600205584185478[25] = 0.0;
   out_5555600205584185478[26] = 0.0;
   out_5555600205584185478[27] = 0.0;
   out_5555600205584185478[28] = 0.0;
   out_5555600205584185478[29] = 0.0;
   out_5555600205584185478[30] = 0.0;
   out_5555600205584185478[31] = 0.0;
   out_5555600205584185478[32] = 0.0;
   out_5555600205584185478[33] = 0.0;
   out_5555600205584185478[34] = 0.0;
   out_5555600205584185478[35] = 0.0;
   out_5555600205584185478[36] = 0.0;
   out_5555600205584185478[37] = 0.0;
   out_5555600205584185478[38] = 1.0;
   out_5555600205584185478[39] = 0.0;
   out_5555600205584185478[40] = 0.0;
   out_5555600205584185478[41] = 0.0;
   out_5555600205584185478[42] = 0.0;
   out_5555600205584185478[43] = 0.0;
   out_5555600205584185478[44] = 0.0;
   out_5555600205584185478[45] = 0.0;
   out_5555600205584185478[46] = 0.0;
   out_5555600205584185478[47] = 0.0;
   out_5555600205584185478[48] = 0.0;
   out_5555600205584185478[49] = 0.0;
   out_5555600205584185478[50] = 0.0;
   out_5555600205584185478[51] = 0.0;
   out_5555600205584185478[52] = 0.0;
   out_5555600205584185478[53] = 0.0;
   out_5555600205584185478[54] = 0.0;
   out_5555600205584185478[55] = 0.0;
   out_5555600205584185478[56] = 0.0;
   out_5555600205584185478[57] = 1.0;
   out_5555600205584185478[58] = 0.0;
   out_5555600205584185478[59] = 0.0;
   out_5555600205584185478[60] = 0.0;
   out_5555600205584185478[61] = 0.0;
   out_5555600205584185478[62] = 0.0;
   out_5555600205584185478[63] = 0.0;
   out_5555600205584185478[64] = 0.0;
   out_5555600205584185478[65] = 0.0;
   out_5555600205584185478[66] = 0.0;
   out_5555600205584185478[67] = 0.0;
   out_5555600205584185478[68] = 0.0;
   out_5555600205584185478[69] = 0.0;
   out_5555600205584185478[70] = 0.0;
   out_5555600205584185478[71] = 0.0;
   out_5555600205584185478[72] = 0.0;
   out_5555600205584185478[73] = 0.0;
   out_5555600205584185478[74] = 0.0;
   out_5555600205584185478[75] = 0.0;
   out_5555600205584185478[76] = 1.0;
   out_5555600205584185478[77] = 0.0;
   out_5555600205584185478[78] = 0.0;
   out_5555600205584185478[79] = 0.0;
   out_5555600205584185478[80] = 0.0;
   out_5555600205584185478[81] = 0.0;
   out_5555600205584185478[82] = 0.0;
   out_5555600205584185478[83] = 0.0;
   out_5555600205584185478[84] = 0.0;
   out_5555600205584185478[85] = 0.0;
   out_5555600205584185478[86] = 0.0;
   out_5555600205584185478[87] = 0.0;
   out_5555600205584185478[88] = 0.0;
   out_5555600205584185478[89] = 0.0;
   out_5555600205584185478[90] = 0.0;
   out_5555600205584185478[91] = 0.0;
   out_5555600205584185478[92] = 0.0;
   out_5555600205584185478[93] = 0.0;
   out_5555600205584185478[94] = 0.0;
   out_5555600205584185478[95] = 1.0;
   out_5555600205584185478[96] = 0.0;
   out_5555600205584185478[97] = 0.0;
   out_5555600205584185478[98] = 0.0;
   out_5555600205584185478[99] = 0.0;
   out_5555600205584185478[100] = 0.0;
   out_5555600205584185478[101] = 0.0;
   out_5555600205584185478[102] = 0.0;
   out_5555600205584185478[103] = 0.0;
   out_5555600205584185478[104] = 0.0;
   out_5555600205584185478[105] = 0.0;
   out_5555600205584185478[106] = 0.0;
   out_5555600205584185478[107] = 0.0;
   out_5555600205584185478[108] = 0.0;
   out_5555600205584185478[109] = 0.0;
   out_5555600205584185478[110] = 0.0;
   out_5555600205584185478[111] = 0.0;
   out_5555600205584185478[112] = 0.0;
   out_5555600205584185478[113] = 0.0;
   out_5555600205584185478[114] = 1.0;
   out_5555600205584185478[115] = 0.0;
   out_5555600205584185478[116] = 0.0;
   out_5555600205584185478[117] = 0.0;
   out_5555600205584185478[118] = 0.0;
   out_5555600205584185478[119] = 0.0;
   out_5555600205584185478[120] = 0.0;
   out_5555600205584185478[121] = 0.0;
   out_5555600205584185478[122] = 0.0;
   out_5555600205584185478[123] = 0.0;
   out_5555600205584185478[124] = 0.0;
   out_5555600205584185478[125] = 0.0;
   out_5555600205584185478[126] = 0.0;
   out_5555600205584185478[127] = 0.0;
   out_5555600205584185478[128] = 0.0;
   out_5555600205584185478[129] = 0.0;
   out_5555600205584185478[130] = 0.0;
   out_5555600205584185478[131] = 0.0;
   out_5555600205584185478[132] = 0.0;
   out_5555600205584185478[133] = 1.0;
   out_5555600205584185478[134] = 0.0;
   out_5555600205584185478[135] = 0.0;
   out_5555600205584185478[136] = 0.0;
   out_5555600205584185478[137] = 0.0;
   out_5555600205584185478[138] = 0.0;
   out_5555600205584185478[139] = 0.0;
   out_5555600205584185478[140] = 0.0;
   out_5555600205584185478[141] = 0.0;
   out_5555600205584185478[142] = 0.0;
   out_5555600205584185478[143] = 0.0;
   out_5555600205584185478[144] = 0.0;
   out_5555600205584185478[145] = 0.0;
   out_5555600205584185478[146] = 0.0;
   out_5555600205584185478[147] = 0.0;
   out_5555600205584185478[148] = 0.0;
   out_5555600205584185478[149] = 0.0;
   out_5555600205584185478[150] = 0.0;
   out_5555600205584185478[151] = 0.0;
   out_5555600205584185478[152] = 1.0;
   out_5555600205584185478[153] = 0.0;
   out_5555600205584185478[154] = 0.0;
   out_5555600205584185478[155] = 0.0;
   out_5555600205584185478[156] = 0.0;
   out_5555600205584185478[157] = 0.0;
   out_5555600205584185478[158] = 0.0;
   out_5555600205584185478[159] = 0.0;
   out_5555600205584185478[160] = 0.0;
   out_5555600205584185478[161] = 0.0;
   out_5555600205584185478[162] = 0.0;
   out_5555600205584185478[163] = 0.0;
   out_5555600205584185478[164] = 0.0;
   out_5555600205584185478[165] = 0.0;
   out_5555600205584185478[166] = 0.0;
   out_5555600205584185478[167] = 0.0;
   out_5555600205584185478[168] = 0.0;
   out_5555600205584185478[169] = 0.0;
   out_5555600205584185478[170] = 0.0;
   out_5555600205584185478[171] = 1.0;
   out_5555600205584185478[172] = 0.0;
   out_5555600205584185478[173] = 0.0;
   out_5555600205584185478[174] = 0.0;
   out_5555600205584185478[175] = 0.0;
   out_5555600205584185478[176] = 0.0;
   out_5555600205584185478[177] = 0.0;
   out_5555600205584185478[178] = 0.0;
   out_5555600205584185478[179] = 0.0;
   out_5555600205584185478[180] = 0.0;
   out_5555600205584185478[181] = 0.0;
   out_5555600205584185478[182] = 0.0;
   out_5555600205584185478[183] = 0.0;
   out_5555600205584185478[184] = 0.0;
   out_5555600205584185478[185] = 0.0;
   out_5555600205584185478[186] = 0.0;
   out_5555600205584185478[187] = 0.0;
   out_5555600205584185478[188] = 0.0;
   out_5555600205584185478[189] = 0.0;
   out_5555600205584185478[190] = 1.0;
   out_5555600205584185478[191] = 0.0;
   out_5555600205584185478[192] = 0.0;
   out_5555600205584185478[193] = 0.0;
   out_5555600205584185478[194] = 0.0;
   out_5555600205584185478[195] = 0.0;
   out_5555600205584185478[196] = 0.0;
   out_5555600205584185478[197] = 0.0;
   out_5555600205584185478[198] = 0.0;
   out_5555600205584185478[199] = 0.0;
   out_5555600205584185478[200] = 0.0;
   out_5555600205584185478[201] = 0.0;
   out_5555600205584185478[202] = 0.0;
   out_5555600205584185478[203] = 0.0;
   out_5555600205584185478[204] = 0.0;
   out_5555600205584185478[205] = 0.0;
   out_5555600205584185478[206] = 0.0;
   out_5555600205584185478[207] = 0.0;
   out_5555600205584185478[208] = 0.0;
   out_5555600205584185478[209] = 1.0;
   out_5555600205584185478[210] = 0.0;
   out_5555600205584185478[211] = 0.0;
   out_5555600205584185478[212] = 0.0;
   out_5555600205584185478[213] = 0.0;
   out_5555600205584185478[214] = 0.0;
   out_5555600205584185478[215] = 0.0;
   out_5555600205584185478[216] = 0.0;
   out_5555600205584185478[217] = 0.0;
   out_5555600205584185478[218] = 0.0;
   out_5555600205584185478[219] = 0.0;
   out_5555600205584185478[220] = 0.0;
   out_5555600205584185478[221] = 0.0;
   out_5555600205584185478[222] = 0.0;
   out_5555600205584185478[223] = 0.0;
   out_5555600205584185478[224] = 0.0;
   out_5555600205584185478[225] = 0.0;
   out_5555600205584185478[226] = 0.0;
   out_5555600205584185478[227] = 0.0;
   out_5555600205584185478[228] = 1.0;
   out_5555600205584185478[229] = 0.0;
   out_5555600205584185478[230] = 0.0;
   out_5555600205584185478[231] = 0.0;
   out_5555600205584185478[232] = 0.0;
   out_5555600205584185478[233] = 0.0;
   out_5555600205584185478[234] = 0.0;
   out_5555600205584185478[235] = 0.0;
   out_5555600205584185478[236] = 0.0;
   out_5555600205584185478[237] = 0.0;
   out_5555600205584185478[238] = 0.0;
   out_5555600205584185478[239] = 0.0;
   out_5555600205584185478[240] = 0.0;
   out_5555600205584185478[241] = 0.0;
   out_5555600205584185478[242] = 0.0;
   out_5555600205584185478[243] = 0.0;
   out_5555600205584185478[244] = 0.0;
   out_5555600205584185478[245] = 0.0;
   out_5555600205584185478[246] = 0.0;
   out_5555600205584185478[247] = 1.0;
   out_5555600205584185478[248] = 0.0;
   out_5555600205584185478[249] = 0.0;
   out_5555600205584185478[250] = 0.0;
   out_5555600205584185478[251] = 0.0;
   out_5555600205584185478[252] = 0.0;
   out_5555600205584185478[253] = 0.0;
   out_5555600205584185478[254] = 0.0;
   out_5555600205584185478[255] = 0.0;
   out_5555600205584185478[256] = 0.0;
   out_5555600205584185478[257] = 0.0;
   out_5555600205584185478[258] = 0.0;
   out_5555600205584185478[259] = 0.0;
   out_5555600205584185478[260] = 0.0;
   out_5555600205584185478[261] = 0.0;
   out_5555600205584185478[262] = 0.0;
   out_5555600205584185478[263] = 0.0;
   out_5555600205584185478[264] = 0.0;
   out_5555600205584185478[265] = 0.0;
   out_5555600205584185478[266] = 1.0;
   out_5555600205584185478[267] = 0.0;
   out_5555600205584185478[268] = 0.0;
   out_5555600205584185478[269] = 0.0;
   out_5555600205584185478[270] = 0.0;
   out_5555600205584185478[271] = 0.0;
   out_5555600205584185478[272] = 0.0;
   out_5555600205584185478[273] = 0.0;
   out_5555600205584185478[274] = 0.0;
   out_5555600205584185478[275] = 0.0;
   out_5555600205584185478[276] = 0.0;
   out_5555600205584185478[277] = 0.0;
   out_5555600205584185478[278] = 0.0;
   out_5555600205584185478[279] = 0.0;
   out_5555600205584185478[280] = 0.0;
   out_5555600205584185478[281] = 0.0;
   out_5555600205584185478[282] = 0.0;
   out_5555600205584185478[283] = 0.0;
   out_5555600205584185478[284] = 0.0;
   out_5555600205584185478[285] = 1.0;
   out_5555600205584185478[286] = 0.0;
   out_5555600205584185478[287] = 0.0;
   out_5555600205584185478[288] = 0.0;
   out_5555600205584185478[289] = 0.0;
   out_5555600205584185478[290] = 0.0;
   out_5555600205584185478[291] = 0.0;
   out_5555600205584185478[292] = 0.0;
   out_5555600205584185478[293] = 0.0;
   out_5555600205584185478[294] = 0.0;
   out_5555600205584185478[295] = 0.0;
   out_5555600205584185478[296] = 0.0;
   out_5555600205584185478[297] = 0.0;
   out_5555600205584185478[298] = 0.0;
   out_5555600205584185478[299] = 0.0;
   out_5555600205584185478[300] = 0.0;
   out_5555600205584185478[301] = 0.0;
   out_5555600205584185478[302] = 0.0;
   out_5555600205584185478[303] = 0.0;
   out_5555600205584185478[304] = 1.0;
   out_5555600205584185478[305] = 0.0;
   out_5555600205584185478[306] = 0.0;
   out_5555600205584185478[307] = 0.0;
   out_5555600205584185478[308] = 0.0;
   out_5555600205584185478[309] = 0.0;
   out_5555600205584185478[310] = 0.0;
   out_5555600205584185478[311] = 0.0;
   out_5555600205584185478[312] = 0.0;
   out_5555600205584185478[313] = 0.0;
   out_5555600205584185478[314] = 0.0;
   out_5555600205584185478[315] = 0.0;
   out_5555600205584185478[316] = 0.0;
   out_5555600205584185478[317] = 0.0;
   out_5555600205584185478[318] = 0.0;
   out_5555600205584185478[319] = 0.0;
   out_5555600205584185478[320] = 0.0;
   out_5555600205584185478[321] = 0.0;
   out_5555600205584185478[322] = 0.0;
   out_5555600205584185478[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1834893773028494468) {
   out_1834893773028494468[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1834893773028494468[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1834893773028494468[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1834893773028494468[3] = dt*state[12] + state[3];
   out_1834893773028494468[4] = dt*state[13] + state[4];
   out_1834893773028494468[5] = dt*state[14] + state[5];
   out_1834893773028494468[6] = state[6];
   out_1834893773028494468[7] = state[7];
   out_1834893773028494468[8] = state[8];
   out_1834893773028494468[9] = state[9];
   out_1834893773028494468[10] = state[10];
   out_1834893773028494468[11] = state[11];
   out_1834893773028494468[12] = state[12];
   out_1834893773028494468[13] = state[13];
   out_1834893773028494468[14] = state[14];
   out_1834893773028494468[15] = state[15];
   out_1834893773028494468[16] = state[16];
   out_1834893773028494468[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4821520291802949801) {
   out_4821520291802949801[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4821520291802949801[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4821520291802949801[2] = 0;
   out_4821520291802949801[3] = 0;
   out_4821520291802949801[4] = 0;
   out_4821520291802949801[5] = 0;
   out_4821520291802949801[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4821520291802949801[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4821520291802949801[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4821520291802949801[9] = 0;
   out_4821520291802949801[10] = 0;
   out_4821520291802949801[11] = 0;
   out_4821520291802949801[12] = 0;
   out_4821520291802949801[13] = 0;
   out_4821520291802949801[14] = 0;
   out_4821520291802949801[15] = 0;
   out_4821520291802949801[16] = 0;
   out_4821520291802949801[17] = 0;
   out_4821520291802949801[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4821520291802949801[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4821520291802949801[20] = 0;
   out_4821520291802949801[21] = 0;
   out_4821520291802949801[22] = 0;
   out_4821520291802949801[23] = 0;
   out_4821520291802949801[24] = 0;
   out_4821520291802949801[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4821520291802949801[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4821520291802949801[27] = 0;
   out_4821520291802949801[28] = 0;
   out_4821520291802949801[29] = 0;
   out_4821520291802949801[30] = 0;
   out_4821520291802949801[31] = 0;
   out_4821520291802949801[32] = 0;
   out_4821520291802949801[33] = 0;
   out_4821520291802949801[34] = 0;
   out_4821520291802949801[35] = 0;
   out_4821520291802949801[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4821520291802949801[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4821520291802949801[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4821520291802949801[39] = 0;
   out_4821520291802949801[40] = 0;
   out_4821520291802949801[41] = 0;
   out_4821520291802949801[42] = 0;
   out_4821520291802949801[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4821520291802949801[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4821520291802949801[45] = 0;
   out_4821520291802949801[46] = 0;
   out_4821520291802949801[47] = 0;
   out_4821520291802949801[48] = 0;
   out_4821520291802949801[49] = 0;
   out_4821520291802949801[50] = 0;
   out_4821520291802949801[51] = 0;
   out_4821520291802949801[52] = 0;
   out_4821520291802949801[53] = 0;
   out_4821520291802949801[54] = 0;
   out_4821520291802949801[55] = 0;
   out_4821520291802949801[56] = 0;
   out_4821520291802949801[57] = 1;
   out_4821520291802949801[58] = 0;
   out_4821520291802949801[59] = 0;
   out_4821520291802949801[60] = 0;
   out_4821520291802949801[61] = 0;
   out_4821520291802949801[62] = 0;
   out_4821520291802949801[63] = 0;
   out_4821520291802949801[64] = 0;
   out_4821520291802949801[65] = 0;
   out_4821520291802949801[66] = dt;
   out_4821520291802949801[67] = 0;
   out_4821520291802949801[68] = 0;
   out_4821520291802949801[69] = 0;
   out_4821520291802949801[70] = 0;
   out_4821520291802949801[71] = 0;
   out_4821520291802949801[72] = 0;
   out_4821520291802949801[73] = 0;
   out_4821520291802949801[74] = 0;
   out_4821520291802949801[75] = 0;
   out_4821520291802949801[76] = 1;
   out_4821520291802949801[77] = 0;
   out_4821520291802949801[78] = 0;
   out_4821520291802949801[79] = 0;
   out_4821520291802949801[80] = 0;
   out_4821520291802949801[81] = 0;
   out_4821520291802949801[82] = 0;
   out_4821520291802949801[83] = 0;
   out_4821520291802949801[84] = 0;
   out_4821520291802949801[85] = dt;
   out_4821520291802949801[86] = 0;
   out_4821520291802949801[87] = 0;
   out_4821520291802949801[88] = 0;
   out_4821520291802949801[89] = 0;
   out_4821520291802949801[90] = 0;
   out_4821520291802949801[91] = 0;
   out_4821520291802949801[92] = 0;
   out_4821520291802949801[93] = 0;
   out_4821520291802949801[94] = 0;
   out_4821520291802949801[95] = 1;
   out_4821520291802949801[96] = 0;
   out_4821520291802949801[97] = 0;
   out_4821520291802949801[98] = 0;
   out_4821520291802949801[99] = 0;
   out_4821520291802949801[100] = 0;
   out_4821520291802949801[101] = 0;
   out_4821520291802949801[102] = 0;
   out_4821520291802949801[103] = 0;
   out_4821520291802949801[104] = dt;
   out_4821520291802949801[105] = 0;
   out_4821520291802949801[106] = 0;
   out_4821520291802949801[107] = 0;
   out_4821520291802949801[108] = 0;
   out_4821520291802949801[109] = 0;
   out_4821520291802949801[110] = 0;
   out_4821520291802949801[111] = 0;
   out_4821520291802949801[112] = 0;
   out_4821520291802949801[113] = 0;
   out_4821520291802949801[114] = 1;
   out_4821520291802949801[115] = 0;
   out_4821520291802949801[116] = 0;
   out_4821520291802949801[117] = 0;
   out_4821520291802949801[118] = 0;
   out_4821520291802949801[119] = 0;
   out_4821520291802949801[120] = 0;
   out_4821520291802949801[121] = 0;
   out_4821520291802949801[122] = 0;
   out_4821520291802949801[123] = 0;
   out_4821520291802949801[124] = 0;
   out_4821520291802949801[125] = 0;
   out_4821520291802949801[126] = 0;
   out_4821520291802949801[127] = 0;
   out_4821520291802949801[128] = 0;
   out_4821520291802949801[129] = 0;
   out_4821520291802949801[130] = 0;
   out_4821520291802949801[131] = 0;
   out_4821520291802949801[132] = 0;
   out_4821520291802949801[133] = 1;
   out_4821520291802949801[134] = 0;
   out_4821520291802949801[135] = 0;
   out_4821520291802949801[136] = 0;
   out_4821520291802949801[137] = 0;
   out_4821520291802949801[138] = 0;
   out_4821520291802949801[139] = 0;
   out_4821520291802949801[140] = 0;
   out_4821520291802949801[141] = 0;
   out_4821520291802949801[142] = 0;
   out_4821520291802949801[143] = 0;
   out_4821520291802949801[144] = 0;
   out_4821520291802949801[145] = 0;
   out_4821520291802949801[146] = 0;
   out_4821520291802949801[147] = 0;
   out_4821520291802949801[148] = 0;
   out_4821520291802949801[149] = 0;
   out_4821520291802949801[150] = 0;
   out_4821520291802949801[151] = 0;
   out_4821520291802949801[152] = 1;
   out_4821520291802949801[153] = 0;
   out_4821520291802949801[154] = 0;
   out_4821520291802949801[155] = 0;
   out_4821520291802949801[156] = 0;
   out_4821520291802949801[157] = 0;
   out_4821520291802949801[158] = 0;
   out_4821520291802949801[159] = 0;
   out_4821520291802949801[160] = 0;
   out_4821520291802949801[161] = 0;
   out_4821520291802949801[162] = 0;
   out_4821520291802949801[163] = 0;
   out_4821520291802949801[164] = 0;
   out_4821520291802949801[165] = 0;
   out_4821520291802949801[166] = 0;
   out_4821520291802949801[167] = 0;
   out_4821520291802949801[168] = 0;
   out_4821520291802949801[169] = 0;
   out_4821520291802949801[170] = 0;
   out_4821520291802949801[171] = 1;
   out_4821520291802949801[172] = 0;
   out_4821520291802949801[173] = 0;
   out_4821520291802949801[174] = 0;
   out_4821520291802949801[175] = 0;
   out_4821520291802949801[176] = 0;
   out_4821520291802949801[177] = 0;
   out_4821520291802949801[178] = 0;
   out_4821520291802949801[179] = 0;
   out_4821520291802949801[180] = 0;
   out_4821520291802949801[181] = 0;
   out_4821520291802949801[182] = 0;
   out_4821520291802949801[183] = 0;
   out_4821520291802949801[184] = 0;
   out_4821520291802949801[185] = 0;
   out_4821520291802949801[186] = 0;
   out_4821520291802949801[187] = 0;
   out_4821520291802949801[188] = 0;
   out_4821520291802949801[189] = 0;
   out_4821520291802949801[190] = 1;
   out_4821520291802949801[191] = 0;
   out_4821520291802949801[192] = 0;
   out_4821520291802949801[193] = 0;
   out_4821520291802949801[194] = 0;
   out_4821520291802949801[195] = 0;
   out_4821520291802949801[196] = 0;
   out_4821520291802949801[197] = 0;
   out_4821520291802949801[198] = 0;
   out_4821520291802949801[199] = 0;
   out_4821520291802949801[200] = 0;
   out_4821520291802949801[201] = 0;
   out_4821520291802949801[202] = 0;
   out_4821520291802949801[203] = 0;
   out_4821520291802949801[204] = 0;
   out_4821520291802949801[205] = 0;
   out_4821520291802949801[206] = 0;
   out_4821520291802949801[207] = 0;
   out_4821520291802949801[208] = 0;
   out_4821520291802949801[209] = 1;
   out_4821520291802949801[210] = 0;
   out_4821520291802949801[211] = 0;
   out_4821520291802949801[212] = 0;
   out_4821520291802949801[213] = 0;
   out_4821520291802949801[214] = 0;
   out_4821520291802949801[215] = 0;
   out_4821520291802949801[216] = 0;
   out_4821520291802949801[217] = 0;
   out_4821520291802949801[218] = 0;
   out_4821520291802949801[219] = 0;
   out_4821520291802949801[220] = 0;
   out_4821520291802949801[221] = 0;
   out_4821520291802949801[222] = 0;
   out_4821520291802949801[223] = 0;
   out_4821520291802949801[224] = 0;
   out_4821520291802949801[225] = 0;
   out_4821520291802949801[226] = 0;
   out_4821520291802949801[227] = 0;
   out_4821520291802949801[228] = 1;
   out_4821520291802949801[229] = 0;
   out_4821520291802949801[230] = 0;
   out_4821520291802949801[231] = 0;
   out_4821520291802949801[232] = 0;
   out_4821520291802949801[233] = 0;
   out_4821520291802949801[234] = 0;
   out_4821520291802949801[235] = 0;
   out_4821520291802949801[236] = 0;
   out_4821520291802949801[237] = 0;
   out_4821520291802949801[238] = 0;
   out_4821520291802949801[239] = 0;
   out_4821520291802949801[240] = 0;
   out_4821520291802949801[241] = 0;
   out_4821520291802949801[242] = 0;
   out_4821520291802949801[243] = 0;
   out_4821520291802949801[244] = 0;
   out_4821520291802949801[245] = 0;
   out_4821520291802949801[246] = 0;
   out_4821520291802949801[247] = 1;
   out_4821520291802949801[248] = 0;
   out_4821520291802949801[249] = 0;
   out_4821520291802949801[250] = 0;
   out_4821520291802949801[251] = 0;
   out_4821520291802949801[252] = 0;
   out_4821520291802949801[253] = 0;
   out_4821520291802949801[254] = 0;
   out_4821520291802949801[255] = 0;
   out_4821520291802949801[256] = 0;
   out_4821520291802949801[257] = 0;
   out_4821520291802949801[258] = 0;
   out_4821520291802949801[259] = 0;
   out_4821520291802949801[260] = 0;
   out_4821520291802949801[261] = 0;
   out_4821520291802949801[262] = 0;
   out_4821520291802949801[263] = 0;
   out_4821520291802949801[264] = 0;
   out_4821520291802949801[265] = 0;
   out_4821520291802949801[266] = 1;
   out_4821520291802949801[267] = 0;
   out_4821520291802949801[268] = 0;
   out_4821520291802949801[269] = 0;
   out_4821520291802949801[270] = 0;
   out_4821520291802949801[271] = 0;
   out_4821520291802949801[272] = 0;
   out_4821520291802949801[273] = 0;
   out_4821520291802949801[274] = 0;
   out_4821520291802949801[275] = 0;
   out_4821520291802949801[276] = 0;
   out_4821520291802949801[277] = 0;
   out_4821520291802949801[278] = 0;
   out_4821520291802949801[279] = 0;
   out_4821520291802949801[280] = 0;
   out_4821520291802949801[281] = 0;
   out_4821520291802949801[282] = 0;
   out_4821520291802949801[283] = 0;
   out_4821520291802949801[284] = 0;
   out_4821520291802949801[285] = 1;
   out_4821520291802949801[286] = 0;
   out_4821520291802949801[287] = 0;
   out_4821520291802949801[288] = 0;
   out_4821520291802949801[289] = 0;
   out_4821520291802949801[290] = 0;
   out_4821520291802949801[291] = 0;
   out_4821520291802949801[292] = 0;
   out_4821520291802949801[293] = 0;
   out_4821520291802949801[294] = 0;
   out_4821520291802949801[295] = 0;
   out_4821520291802949801[296] = 0;
   out_4821520291802949801[297] = 0;
   out_4821520291802949801[298] = 0;
   out_4821520291802949801[299] = 0;
   out_4821520291802949801[300] = 0;
   out_4821520291802949801[301] = 0;
   out_4821520291802949801[302] = 0;
   out_4821520291802949801[303] = 0;
   out_4821520291802949801[304] = 1;
   out_4821520291802949801[305] = 0;
   out_4821520291802949801[306] = 0;
   out_4821520291802949801[307] = 0;
   out_4821520291802949801[308] = 0;
   out_4821520291802949801[309] = 0;
   out_4821520291802949801[310] = 0;
   out_4821520291802949801[311] = 0;
   out_4821520291802949801[312] = 0;
   out_4821520291802949801[313] = 0;
   out_4821520291802949801[314] = 0;
   out_4821520291802949801[315] = 0;
   out_4821520291802949801[316] = 0;
   out_4821520291802949801[317] = 0;
   out_4821520291802949801[318] = 0;
   out_4821520291802949801[319] = 0;
   out_4821520291802949801[320] = 0;
   out_4821520291802949801[321] = 0;
   out_4821520291802949801[322] = 0;
   out_4821520291802949801[323] = 1;
}
void h_4(double *state, double *unused, double *out_844880312854774316) {
   out_844880312854774316[0] = state[6] + state[9];
   out_844880312854774316[1] = state[7] + state[10];
   out_844880312854774316[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3388761460473635864) {
   out_3388761460473635864[0] = 0;
   out_3388761460473635864[1] = 0;
   out_3388761460473635864[2] = 0;
   out_3388761460473635864[3] = 0;
   out_3388761460473635864[4] = 0;
   out_3388761460473635864[5] = 0;
   out_3388761460473635864[6] = 1;
   out_3388761460473635864[7] = 0;
   out_3388761460473635864[8] = 0;
   out_3388761460473635864[9] = 1;
   out_3388761460473635864[10] = 0;
   out_3388761460473635864[11] = 0;
   out_3388761460473635864[12] = 0;
   out_3388761460473635864[13] = 0;
   out_3388761460473635864[14] = 0;
   out_3388761460473635864[15] = 0;
   out_3388761460473635864[16] = 0;
   out_3388761460473635864[17] = 0;
   out_3388761460473635864[18] = 0;
   out_3388761460473635864[19] = 0;
   out_3388761460473635864[20] = 0;
   out_3388761460473635864[21] = 0;
   out_3388761460473635864[22] = 0;
   out_3388761460473635864[23] = 0;
   out_3388761460473635864[24] = 0;
   out_3388761460473635864[25] = 1;
   out_3388761460473635864[26] = 0;
   out_3388761460473635864[27] = 0;
   out_3388761460473635864[28] = 1;
   out_3388761460473635864[29] = 0;
   out_3388761460473635864[30] = 0;
   out_3388761460473635864[31] = 0;
   out_3388761460473635864[32] = 0;
   out_3388761460473635864[33] = 0;
   out_3388761460473635864[34] = 0;
   out_3388761460473635864[35] = 0;
   out_3388761460473635864[36] = 0;
   out_3388761460473635864[37] = 0;
   out_3388761460473635864[38] = 0;
   out_3388761460473635864[39] = 0;
   out_3388761460473635864[40] = 0;
   out_3388761460473635864[41] = 0;
   out_3388761460473635864[42] = 0;
   out_3388761460473635864[43] = 0;
   out_3388761460473635864[44] = 1;
   out_3388761460473635864[45] = 0;
   out_3388761460473635864[46] = 0;
   out_3388761460473635864[47] = 1;
   out_3388761460473635864[48] = 0;
   out_3388761460473635864[49] = 0;
   out_3388761460473635864[50] = 0;
   out_3388761460473635864[51] = 0;
   out_3388761460473635864[52] = 0;
   out_3388761460473635864[53] = 0;
}
void h_10(double *state, double *unused, double *out_2440718403493438730) {
   out_2440718403493438730[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2440718403493438730[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2440718403493438730[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_300556735062169610) {
   out_300556735062169610[0] = 0;
   out_300556735062169610[1] = 9.8100000000000005*cos(state[1]);
   out_300556735062169610[2] = 0;
   out_300556735062169610[3] = 0;
   out_300556735062169610[4] = -state[8];
   out_300556735062169610[5] = state[7];
   out_300556735062169610[6] = 0;
   out_300556735062169610[7] = state[5];
   out_300556735062169610[8] = -state[4];
   out_300556735062169610[9] = 0;
   out_300556735062169610[10] = 0;
   out_300556735062169610[11] = 0;
   out_300556735062169610[12] = 1;
   out_300556735062169610[13] = 0;
   out_300556735062169610[14] = 0;
   out_300556735062169610[15] = 1;
   out_300556735062169610[16] = 0;
   out_300556735062169610[17] = 0;
   out_300556735062169610[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_300556735062169610[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_300556735062169610[20] = 0;
   out_300556735062169610[21] = state[8];
   out_300556735062169610[22] = 0;
   out_300556735062169610[23] = -state[6];
   out_300556735062169610[24] = -state[5];
   out_300556735062169610[25] = 0;
   out_300556735062169610[26] = state[3];
   out_300556735062169610[27] = 0;
   out_300556735062169610[28] = 0;
   out_300556735062169610[29] = 0;
   out_300556735062169610[30] = 0;
   out_300556735062169610[31] = 1;
   out_300556735062169610[32] = 0;
   out_300556735062169610[33] = 0;
   out_300556735062169610[34] = 1;
   out_300556735062169610[35] = 0;
   out_300556735062169610[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_300556735062169610[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_300556735062169610[38] = 0;
   out_300556735062169610[39] = -state[7];
   out_300556735062169610[40] = state[6];
   out_300556735062169610[41] = 0;
   out_300556735062169610[42] = state[4];
   out_300556735062169610[43] = -state[3];
   out_300556735062169610[44] = 0;
   out_300556735062169610[45] = 0;
   out_300556735062169610[46] = 0;
   out_300556735062169610[47] = 0;
   out_300556735062169610[48] = 0;
   out_300556735062169610[49] = 0;
   out_300556735062169610[50] = 1;
   out_300556735062169610[51] = 0;
   out_300556735062169610[52] = 0;
   out_300556735062169610[53] = 1;
}
void h_13(double *state, double *unused, double *out_3091723421696896469) {
   out_3091723421696896469[0] = state[3];
   out_3091723421696896469[1] = state[4];
   out_3091723421696896469[2] = state[5];
}
void H_13(double *state, double *unused, double *out_176487635141303063) {
   out_176487635141303063[0] = 0;
   out_176487635141303063[1] = 0;
   out_176487635141303063[2] = 0;
   out_176487635141303063[3] = 1;
   out_176487635141303063[4] = 0;
   out_176487635141303063[5] = 0;
   out_176487635141303063[6] = 0;
   out_176487635141303063[7] = 0;
   out_176487635141303063[8] = 0;
   out_176487635141303063[9] = 0;
   out_176487635141303063[10] = 0;
   out_176487635141303063[11] = 0;
   out_176487635141303063[12] = 0;
   out_176487635141303063[13] = 0;
   out_176487635141303063[14] = 0;
   out_176487635141303063[15] = 0;
   out_176487635141303063[16] = 0;
   out_176487635141303063[17] = 0;
   out_176487635141303063[18] = 0;
   out_176487635141303063[19] = 0;
   out_176487635141303063[20] = 0;
   out_176487635141303063[21] = 0;
   out_176487635141303063[22] = 1;
   out_176487635141303063[23] = 0;
   out_176487635141303063[24] = 0;
   out_176487635141303063[25] = 0;
   out_176487635141303063[26] = 0;
   out_176487635141303063[27] = 0;
   out_176487635141303063[28] = 0;
   out_176487635141303063[29] = 0;
   out_176487635141303063[30] = 0;
   out_176487635141303063[31] = 0;
   out_176487635141303063[32] = 0;
   out_176487635141303063[33] = 0;
   out_176487635141303063[34] = 0;
   out_176487635141303063[35] = 0;
   out_176487635141303063[36] = 0;
   out_176487635141303063[37] = 0;
   out_176487635141303063[38] = 0;
   out_176487635141303063[39] = 0;
   out_176487635141303063[40] = 0;
   out_176487635141303063[41] = 1;
   out_176487635141303063[42] = 0;
   out_176487635141303063[43] = 0;
   out_176487635141303063[44] = 0;
   out_176487635141303063[45] = 0;
   out_176487635141303063[46] = 0;
   out_176487635141303063[47] = 0;
   out_176487635141303063[48] = 0;
   out_176487635141303063[49] = 0;
   out_176487635141303063[50] = 0;
   out_176487635141303063[51] = 0;
   out_176487635141303063[52] = 0;
   out_176487635141303063[53] = 0;
}
void h_14(double *state, double *unused, double *out_9069388618255276242) {
   out_9069388618255276242[0] = state[6];
   out_9069388618255276242[1] = state[7];
   out_9069388618255276242[2] = state[8];
}
void H_14(double *state, double *unused, double *out_574479395865848665) {
   out_574479395865848665[0] = 0;
   out_574479395865848665[1] = 0;
   out_574479395865848665[2] = 0;
   out_574479395865848665[3] = 0;
   out_574479395865848665[4] = 0;
   out_574479395865848665[5] = 0;
   out_574479395865848665[6] = 1;
   out_574479395865848665[7] = 0;
   out_574479395865848665[8] = 0;
   out_574479395865848665[9] = 0;
   out_574479395865848665[10] = 0;
   out_574479395865848665[11] = 0;
   out_574479395865848665[12] = 0;
   out_574479395865848665[13] = 0;
   out_574479395865848665[14] = 0;
   out_574479395865848665[15] = 0;
   out_574479395865848665[16] = 0;
   out_574479395865848665[17] = 0;
   out_574479395865848665[18] = 0;
   out_574479395865848665[19] = 0;
   out_574479395865848665[20] = 0;
   out_574479395865848665[21] = 0;
   out_574479395865848665[22] = 0;
   out_574479395865848665[23] = 0;
   out_574479395865848665[24] = 0;
   out_574479395865848665[25] = 1;
   out_574479395865848665[26] = 0;
   out_574479395865848665[27] = 0;
   out_574479395865848665[28] = 0;
   out_574479395865848665[29] = 0;
   out_574479395865848665[30] = 0;
   out_574479395865848665[31] = 0;
   out_574479395865848665[32] = 0;
   out_574479395865848665[33] = 0;
   out_574479395865848665[34] = 0;
   out_574479395865848665[35] = 0;
   out_574479395865848665[36] = 0;
   out_574479395865848665[37] = 0;
   out_574479395865848665[38] = 0;
   out_574479395865848665[39] = 0;
   out_574479395865848665[40] = 0;
   out_574479395865848665[41] = 0;
   out_574479395865848665[42] = 0;
   out_574479395865848665[43] = 0;
   out_574479395865848665[44] = 1;
   out_574479395865848665[45] = 0;
   out_574479395865848665[46] = 0;
   out_574479395865848665[47] = 0;
   out_574479395865848665[48] = 0;
   out_574479395865848665[49] = 0;
   out_574479395865848665[50] = 0;
   out_574479395865848665[51] = 0;
   out_574479395865848665[52] = 0;
   out_574479395865848665[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_1509083267251830649) {
  err_fun(nom_x, delta_x, out_1509083267251830649);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1626315071309903362) {
  inv_err_fun(nom_x, true_x, out_1626315071309903362);
}
void pose_H_mod_fun(double *state, double *out_5555600205584185478) {
  H_mod_fun(state, out_5555600205584185478);
}
void pose_f_fun(double *state, double dt, double *out_1834893773028494468) {
  f_fun(state,  dt, out_1834893773028494468);
}
void pose_F_fun(double *state, double dt, double *out_4821520291802949801) {
  F_fun(state,  dt, out_4821520291802949801);
}
void pose_h_4(double *state, double *unused, double *out_844880312854774316) {
  h_4(state, unused, out_844880312854774316);
}
void pose_H_4(double *state, double *unused, double *out_3388761460473635864) {
  H_4(state, unused, out_3388761460473635864);
}
void pose_h_10(double *state, double *unused, double *out_2440718403493438730) {
  h_10(state, unused, out_2440718403493438730);
}
void pose_H_10(double *state, double *unused, double *out_300556735062169610) {
  H_10(state, unused, out_300556735062169610);
}
void pose_h_13(double *state, double *unused, double *out_3091723421696896469) {
  h_13(state, unused, out_3091723421696896469);
}
void pose_H_13(double *state, double *unused, double *out_176487635141303063) {
  H_13(state, unused, out_176487635141303063);
}
void pose_h_14(double *state, double *unused, double *out_9069388618255276242) {
  h_14(state, unused, out_9069388618255276242);
}
void pose_H_14(double *state, double *unused, double *out_574479395865848665) {
  H_14(state, unused, out_574479395865848665);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
