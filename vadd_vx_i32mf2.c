/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  132, 125, 100, 175, 200, 233, 146, 211, 61, 174, 249, 153, 140, 59, 126, 159, 14, 123, 108, 210, 165, 103, 14, 158, 44, 161, 192, 112, 65, 233, 184, 197, 208, 41, 199, 222, 166, 132, 207, 61, 173, 241, 84, 171, 175, 111, 169, 139, 192, 98, 178, 197, 5, 214, 159, 125, 195, 35, 230, 5, 92, 8, 59, 178
  };
  const int *in1 = &data1[0];
    int data2[] = {
  53, 42, 118, 52, 91, 186, 217, 76, 58, 0, 201, 57, 183, 1, 112, 139, 239, 8, 142, 226, 102, 59, 15, 82, 164, 99, 251, 14, 55, 236, 82, 95, 224, 37, 5, 158, 111, 155, 73, 153, 57, 55, 63, 35, 85, 98, 48, 50, 221, 102, 222, 113, 29, 6, 26, 64, 206, 80, 36, 113, 72, 79, 127, 38
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint32mf2_t out = __riscv_vadd_vx_i32mf2 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  185, 167, 218, 227, 291, 419, 363, 287, 119, 174, 450, 210, 323, 60, 238, 298, 253, 131, 250, 436, 267, 162, 29, 240, 208, 260, 443, 126, 120, 469, 266, 292, 432, 78, 204, 380, 277, 287, 280, 214, 230, 296, 147, 206, 260, 209, 217, 189, 413, 200, 400, 310, 34, 220, 185, 189, 401, 115, 266, 118, 164, 87, 186, 216
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
