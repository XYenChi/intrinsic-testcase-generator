/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  134, 30, 40, 125, 33, 31, 180, 63, 141, 72, 110, 117, 161, 106, 191, 6, 64, 128, 78, 170, 168, 246, 198, 146, 114, 227, 233, 196, 42, 26, 81, 187, 79, 155, 155, 252, 25, 138, 7, 211, 12, 252, 22, 212, 113, 127, 251, 83, 139, 113, 38, 190, 97, 228, 103, 248, 176, 152, 182, 222, 175, 232, 70, 221
  };
  const int *in1 = &data1[0];
    int data2[] = {
  189, 80, 133, 209, 220, 90, 108, 104, 169, 210, 116, 223, 190, 23, 34, 100, 96, 100, 212, 12, 128, 221, 202, 195, 138, 185, 204, 180, 49, 117, 4, 92, 83, 60, 247, 253, 149, 206, 74, 229, 97, 139, 231, 235, 114, 94, 176, 181, 244, 158, 87, 186, 75, 250, 8, 162, 46, 181, 235, 81, 89, 32, 244, 182
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint64m1_t out = __riscv_vadd_vx_i64m1 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  323, 110, 173, 334, 253, 121, 288, 167, 310, 282, 226, 340, 351, 129, 225, 106, 160, 228, 290, 182, 296, 467, 400, 341, 252, 412, 437, 376, 91, 143, 85, 279, 162, 215, 402, 505, 174, 344, 81, 440, 109, 391, 253, 447, 227, 221, 427, 264, 383, 271, 125, 376, 172, 478, 111, 410, 222, 333, 417, 303, 264, 264, 314, 403
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