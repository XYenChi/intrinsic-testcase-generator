/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  206, 132, 33, 100, 50, 76, 20, 225, 202, 179, 118, 51, 192, 181, 31, 210, 44, 133, 193, 107, 203, 174, 238, 91, 26, 140, 127, 5, 19, 183, 31, 155, 36, 6, 214, 166, 245, 120, 87, 82, 190, 240, 89, 241, 24, 243, 175, 142, 40, 171, 32, 121, 9, 204, 110, 23, 176, 231, 28, 108, 72, 20, 210, 145
  };
  const int *in1 = &data1[0];
    int data2[] = {
  177, 165, 187, 186, 212, 225, 64, 69, 96, 139, 156, 253, 76, 72, 221, 18, 94, 53, 84, 180, 179, 137, 58, 101, 89, 142, 4, 6, 153, 245, 151, 16, 107, 88, 223, 154, 186, 142, 44, 33, 182, 111, 216, 92, 241, 214, 194, 13, 21, 127, 156, 200, 17, 234, 248, 203, 125, 178, 44, 90, 39, 232, 234, 234
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint16mf4_t out = __riscv_vsub_vv_i16mf4 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  29, -33, -154, -86, -162, -149, -44, 156, 106, 40, -38, -202, 116, 109, -190, 192, -50, 80, 109, -73, 24, 37, 180, -10, -63, -2, 123, -1, -134, -62, -120, 139, -71, -82, -9, 12, 59, -22, 43, 49, 8, 129, -127, 149, -217, 29, -19, 129, 19, 44, -124, -79, -8, -30, -138, -180, 51, 53, -16, 18, 33, -212, -24, -89
  };
  int fail = 0;
  for (int i = 0; i < 64; i++)
     if (golden0[i] != out0_data[i]) {
       printf ("idx=%d golden=%d out=%d\n", i, golden0[i], out0[i]);
       fail++;
     }
  if (fail) {
    return 1;
  } else {
    return 0;
  }
}
