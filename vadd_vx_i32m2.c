/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  40, 7, 13, 79, 190, 17, 86, 188, 226, 81, 224, 134, 203, 245, 77, 133, 103, 93, 248, 133, 193, 61, 156, 11, 35, 115, 132, 105, 220, 7, 127, 24, 156, 87, 62, 31, 213, 117, 44, 218, 181, 185, 182, 13, 139, 30, 100, 97, 127, 178, 88, 57, 191, 39, 57, 248, 185, 71, 2, 183, 13, 82, 186, 127
  };
  const int *in1 = &data1[0];
    int data2[] = {
  220, 73, 65, 145, 107, 179, 213, 148, 218, 28, 99, 68, 182, 246, 152, 101, 12, 232, 69, 37, 21, 221, 48, 204, 208, 184, 241, 113, 220, 10, 31, 27, 164, 89, 242, 119, 254, 95, 79, 240, 24, 8, 90, 135, 155, 15, 40, 85, 118, 200, 61, 188, 127, 164, 136, 32, 196, 113, 24, 178, 138, 37, 31, 189
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint32m2_t out = __riscv_vadd_vx_i32m2 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  260, 80, 78, 224, 297, 196, 299, 336, 444, 109, 323, 202, 385, 491, 229, 234, 115, 325, 317, 170, 214, 282, 204, 215, 243, 299, 373, 218, 440, 17, 158, 51, 320, 176, 304, 150, 467, 212, 123, 458, 205, 193, 272, 148, 294, 45, 140, 182, 245, 378, 149, 245, 318, 203, 193, 280, 381, 184, 26, 361, 151, 119, 217, 316
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
