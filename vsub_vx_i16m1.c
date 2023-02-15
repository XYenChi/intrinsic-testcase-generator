/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  59, 136, 194, 172, 56, 211, 155, 174, 5, 232, 55, 109, 88, 34, 197, 218, 241, 82, 51, 180, 47, 172, 176, 116, 4, 0, 21, 60, 153, 131, 168, 86, 144, 22, 46, 199, 42, 131, 244, 194, 228, 236, 127, 228, 53, 81, 88, 190, 185, 142, 115, 61, 101, 58, 111, 248, 137, 94, 246, 157, 148, 59, 210, 36
  };
  const int *in1 = &data1[0];
    int data2[] = {
  64, 37, 192, 188, 73, 73, 230, 96, 231, 149, 172, 88, 95, 225, 233, 70, 169, 25, 171, 48, 17, 210, 42, 60, 234, 76, 80, 192, 222, 159, 176, 183, 120, 172, 229, 60, 214, 190, 103, 235, 214, 68, 191, 193, 114, 174, 80, 124, 152, 37, 147, 222, 172, 236, 128, 96, 198, 223, 199, 162, 9, 223, 41, 168
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint16m1_t out = __riscv_vsub_vx_i16m1 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  -5, 99, 2, -16, -17, 138, -75, 78, -226, 83, -117, 21, -7, -191, -36, 148, 72, 57, -120, 132, 30, -38, 134, 56, -230, -76, -59, -132, -69, -28, -8, -97, 24, -150, -183, 139, -172, -59, 141, -41, 14, 168, -64, 35, -61, -93, 8, 66, 33, 105, -32, -161, -71, -178, -17, 152, -61, -129, 47, -5, 139, -164, 169, -132
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
