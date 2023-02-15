/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  250, 138, 6, 46, 236, 41, 21, 167, 150, 123, 87, 178, 253, 122, 189, 31, 239, 184, 0, 14, 106, 81, 160, 60, 247, 21, 149, 244, 255, 177, 162, 191, 45, 50, 179, 17, 193, 109, 142, 177, 244, 195, 172, 35, 169, 161, 13, 138, 149, 30, 234, 90, 19, 139, 236, 112, 156, 216, 98, 149, 212, 202, 138, 41
  };
  const int *in1 = &data1[0];
    int data2[] = {
  28, 89, 158, 83, 142, 127, 68, 43, 147, 44, 223, 17, 89, 189, 175, 100, 191, 153, 202, 59, 121, 82, 217, 68, 103, 251, 97, 117, 4, 167, 239, 97, 90, 93, 89, 255, 193, 58, 58, 175, 84, 231, 108, 154, 187, 93, 199, 203, 221, 112, 51, 116, 100, 142, 41, 255, 31, 67, 55, 16, 11, 252, 243, 250
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint16mf4_t out = __riscv_vsub_vx_i16mf4 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  222, 49, -152, -37, 94, -86, -47, 124, 3, 79, -136, 161, 164, -67, 14, -69, 48, 31, -202, -45, -15, -1, -57, -8, 144, -230, 52, 127, 251, 10, -77, 94, -45, -43, 90, -238, 0, 51, 84, 2, 160, -36, 64, -119, -18, 68, -186, -65, -72, -82, 183, -26, -81, -3, 195, -143, 125, 149, 43, 133, 201, -50, -105, -209
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
