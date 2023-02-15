/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  213, 59, 15, 137, 71, 25, 224, 168, 177, 50, 121, 100, 34, 201, 250, 85, 13, 224, 187, 214, 242, 129, 166, 137, 191, 211, 221, 167, 88, 202, 122, 199, 126, 190, 8, 208, 61, 52, 103, 199, 121, 76, 160, 163, 115, 114, 193, 16, 140, 4, 152, 151, 207, 57, 58, 255, 129, 249, 153, 115, 189, 247, 145, 144
  };
  const int *in1 = &data1[0];
    int data2[] = {
  147, 238, 86, 217, 1, 215, 75, 19, 106, 115, 224, 37, 137, 244, 10, 193, 123, 211, 36, 15, 143, 154, 242, 189, 23, 107, 90, 135, 170, 184, 196, 165, 58, 131, 186, 2, 139, 113, 191, 44, 50, 225, 145, 128, 63, 1, 16, 212, 5, 224, 16, 180, 107, 187, 3, 56, 148, 196, 99, 111, 99, 75, 24, 179
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint16m2_t out = __riscv_vsub_vx_i16m2 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  66, -179, -71, -80, 70, -190, 149, 149, 71, -65, -103, 63, -103, -43, 240, -108, -110, 13, 151, 199, 99, -25, -76, -52, 168, 104, 131, 32, -82, 18, -74, 34, 68, 59, -178, 206, -78, -61, -88, 155, 71, -149, 15, 35, 52, 113, 177, -196, 135, -220, 136, -29, 100, -130, 55, 199, -19, 53, 54, 4, 90, 172, 121, -35
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