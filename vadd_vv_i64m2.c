/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  71, 95, 55, 171, 43, 34, 159, 91, 220, 157, 114, 210, 162, 73, 213, 102, 118, 130, 21, 150, 141, 68, 20, 180, 23, 193, 181, 31, 80, 26, 34, 54, 144, 181, 7, 176, 239, 235, 17, 93, 234, 20, 246, 42, 77, 8, 251, 132, 204, 54, 177, 223, 85, 130, 126, 216, 6, 73, 218, 120, 52, 177, 160, 155
  };
  const int *in1 = &data1[0];
    int data2[] = {
  55, 38, 111, 203, 206, 97, 10, 85, 19, 60, 22, 252, 163, 246, 97, 60, 102, 105, 237, 73, 161, 168, 101, 81, 163, 167, 174, 137, 30, 197, 103, 8, 9, 111, 158, 61, 131, 78, 140, 133, 205, 12, 37, 28, 55, 79, 56, 179, 194, 31, 86, 18, 41, 155, 240, 88, 170, 71, 109, 163, 173, 233, 247, 145
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint64m2_t out = __riscv_vadd_vv_i64m2 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  126, 133, 166, 374, 249, 131, 169, 176, 239, 217, 136, 462, 325, 319, 310, 162, 220, 235, 258, 223, 302, 236, 121, 261, 186, 360, 355, 168, 110, 223, 137, 62, 153, 292, 165, 237, 370, 313, 157, 226, 439, 32, 283, 70, 132, 87, 307, 311, 398, 85, 263, 241, 126, 285, 366, 304, 176, 144, 327, 283, 225, 410, 407, 300
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
