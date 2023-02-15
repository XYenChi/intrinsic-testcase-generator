/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  81, 114, 113, 81, 96, 130, 226, 0, 72, 254, 105, 166, 18, 66, 94, 98, 152, 200, 238, 9, 78, 60, 210, 254, 142, 30, 126, 21, 66, 37, 141, 85, 202, 29, 203, 121, 92, 193, 23, 70, 203, 157, 77, 60, 142, 189, 38, 60, 227, 196, 227, 41, 188, 33, 122, 251, 219, 28, 116, 76, 95, 239, 230, 237
  };
  const int *in1 = &data1[0];
    int data2[] = {
  142, 83, 78, 14, 125, 74, 21, 141, 86, 2, 3, 89, 198, 67, 158, 141, 151, 160, 28, 67, 114, 221, 38, 60, 122, 80, 31, 50, 87, 70, 65, 54, 65, 122, 62, 180, 195, 142, 244, 126, 208, 81, 107, 16, 36, 32, 37, 94, 155, 144, 226, 238, 223, 122, 118, 207, 190, 226, 192, 162, 107, 63, 93, 20
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint8m2_t out = __riscv_vsub_vv_i8m2 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  -61, 31, 35, 67, -29, 56, 205, -141, -14, 252, 102, 77, -180, -1, -64, -43, 1, 40, 210, -58, -36, -161, 172, 194, 20, -50, 95, -29, -21, -33, 76, 31, 137, -93, 141, -59, -103, 51, -221, -56, -5, 76, -30, 44, 106, 157, 1, -34, 72, 52, 1, -197, -35, -89, 4, 44, 29, -198, -76, -86, -12, 176, 137, 217
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