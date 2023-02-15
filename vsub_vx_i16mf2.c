/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  50, 110, 229, 47, 132, 154, 62, 214, 159, 227, 28, 112, 5, 19, 6, 199, 71, 205, 133, 109, 151, 89, 99, 5, 233, 180, 190, 10, 216, 56, 18, 237, 82, 123, 218, 210, 116, 133, 46, 99, 149, 15, 159, 20, 100, 102, 209, 43, 47, 100, 90, 122, 66, 111, 111, 227, 85, 112, 131, 40, 197, 84, 45, 248
  };
  const int *in1 = &data1[0];
    int data2[] = {
  181, 94, 202, 241, 94, 228, 161, 249, 34, 115, 5, 178, 111, 37, 194, 0, 23, 146, 151, 232, 98, 154, 253, 104, 203, 194, 22, 76, 166, 58, 61, 59, 18, 63, 99, 62, 173, 243, 245, 84, 248, 206, 103, 98, 13, 242, 197, 131, 53, 76, 17, 214, 155, 141, 115, 102, 82, 55, 85, 156, 8, 99, 161, 132
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint16mf2_t out = __riscv_vsub_vx_i16mf2 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  -131, 16, 27, -194, 38, -74, -99, -35, 125, 112, 23, -66, -106, -18, -188, 199, 48, 59, -18, -123, 53, -65, -154, -99, 30, -14, 168, -66, 50, -2, -43, 178, 64, 60, 119, 148, -57, -110, -199, 15, -99, -191, 56, -78, 87, -140, 12, -88, -6, 24, 73, -92, -89, -30, -4, 125, 3, 57, 46, -116, 189, -15, -116, 116
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