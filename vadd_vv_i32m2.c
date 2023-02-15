/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  196, 250, 42, 218, 81, 55, 164, 75, 226, 175, 120, 73, 11, 208, 89, 93, 190, 154, 89, 15, 72, 16, 101, 84, 147, 139, 241, 152, 219, 160, 137, 252, 64, 21, 82, 228, 219, 145, 5, 210, 216, 145, 74, 206, 243, 0, 6, 52, 55, 83, 130, 235, 131, 103, 28, 199, 198, 46, 180, 103, 97, 156, 148, 216
  };
  const int *in1 = &data1[0];
    int data2[] = {
  246, 106, 118, 67, 61, 150, 241, 162, 209, 9, 61, 18, 175, 139, 163, 108, 52, 248, 120, 196, 9, 183, 226, 43, 139, 247, 119, 91, 99, 188, 180, 224, 7, 75, 116, 208, 157, 123, 136, 171, 8, 26, 140, 235, 232, 102, 190, 161, 46, 37, 94, 146, 207, 224, 101, 180, 138, 234, 244, 40, 114, 115, 108, 65
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint32m2_t out = __riscv_vadd_vv_i32m2 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  442, 356, 160, 285, 142, 205, 405, 237, 435, 184, 181, 91, 186, 347, 252, 201, 242, 402, 209, 211, 81, 199, 327, 127, 286, 386, 360, 243, 318, 348, 317, 476, 71, 96, 198, 436, 376, 268, 141, 381, 224, 171, 214, 441, 475, 102, 196, 213, 101, 120, 224, 381, 338, 327, 129, 379, 336, 280, 424, 143, 211, 271, 256, 281
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