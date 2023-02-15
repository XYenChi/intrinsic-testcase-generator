/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  255, 54, 236, 227, 90, 104, 3, 199, 185, 168, 236, 205, 225, 195, 114, 226, 151, 38, 149, 149, 166, 79, 123, 181, 190, 95, 8, 206, 135, 244, 188, 139, 164, 28, 182, 226, 193, 10, 96, 79, 50, 31, 201, 9, 242, 218, 254, 130, 96, 201, 23, 116, 164, 51, 45, 131, 135, 109, 40, 7, 244, 145, 52, 122
  };
  const int *in1 = &data1[0];
    int data2[] = {
  5, 5, 59, 226, 7, 112, 246, 189, 223, 209, 179, 253, 108, 55, 173, 153, 247, 203, 176, 42, 105, 14, 23, 218, 97, 152, 186, 43, 108, 34, 134, 226, 38, 15, 204, 122, 223, 112, 182, 113, 195, 3, 173, 11, 252, 173, 154, 246, 157, 75, 132, 100, 66, 126, 171, 49, 99, 56, 137, 247, 242, 96, 44, 121
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint32m2_t out = __riscv_vsub_vx_i32m2 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  250, 49, 177, 1, 83, -8, -243, 10, -38, -41, 57, -48, 117, 140, -59, 73, -96, -165, -27, 107, 61, 65, 100, -37, 93, -57, -178, 163, 27, 210, 54, -87, 126, 13, -22, 104, -30, -102, -86, -34, -145, 28, 28, -2, -10, 45, 100, -116, -61, 126, -109, 16, 98, -75, -126, 82, 36, 53, -97, -240, 2, 49, 8, 1
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