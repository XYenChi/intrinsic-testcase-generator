/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  19, 169, 9, 84, 240, 62, 148, 210, 8, 128, 107, 76, 49, 157, 90, 77, 102, 41, 66, 38, 190, 222, 92, 222, 164, 65, 199, 165, 47, 211, 242, 99, 58, 41, 200, 182, 132, 7, 53, 88, 48, 109, 150, 203, 63, 166, 136, 68, 32, 178, 152, 26, 52, 6, 246, 235, 250, 225, 246, 185, 171, 227, 29, 108
  };
  const int *in1 = &data1[0];
    int data2[] = {
  167, 99, 55, 244, 176, 252, 141, 230, 162, 202, 254, 172, 206, 84, 163, 7, 136, 232, 1, 248, 255, 153, 235, 121, 249, 169, 73, 135, 131, 2, 178, 230, 43, 171, 166, 83, 162, 127, 196, 116, 150, 221, 221, 171, 234, 10, 46, 123, 122, 143, 245, 20, 142, 237, 16, 221, 25, 72, 179, 113, 187, 249, 67, 196
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint8mf8_t out = __riscv_vadd_vx_i8mf8 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  186, 268, 64, 328, 416, 314, 289, 440, 170, 330, 361, 248, 255, 241, 253, 84, 238, 273, 67, 286, 445, 375, 327, 343, 413, 234, 272, 300, 178, 213, 420, 329, 101, 212, 366, 265, 294, 134, 249, 204, 198, 330, 371, 374, 297, 176, 182, 191, 154, 321, 397, 46, 194, 243, 262, 456, 275, 297, 425, 298, 358, 476, 96, 304
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