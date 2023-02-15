/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
  93, 86, 61, 164, 156, 171, 130, 183, 218, 172, 198, 201, 42, 187, 121, 142, 142, 194, 169, 55, 113, 252, 2, 223, 70, 12, 152, 212, 170, 187, 52, 204, 5, 158, 106, 137, 224, 195, 14, 3, 224, 60, 20, 97, 223, 101, 136, 124, 241, 240, 180, 9, 22, 83, 142, 212, 245, 158, 135, 170, 255, 187, 145, 139
  };
  const int *in1 = &data1[0];
    int data2[] = {
  51, 63, 60, 252, 175, 254, 160, 92, 78, 188, 247, 167, 199, 70, 217, 62, 100, 230, 6, 17, 86, 42, 101, 231, 205, 54, 27, 189, 86, 92, 170, 155, 79, 247, 71, 182, 150, 50, 196, 242, 138, 19, 143, 43, 152, 225, 196, 167, 121, 3, 190, 83, 59, 109, 142, 162, 132, 159, 35, 17, 107, 110, 47, 171
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint64m4_t out = __riscv_vadd_vv_i64m4 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  144, 149, 121, 416, 331, 425, 290, 275, 296, 360, 445, 368, 241, 257, 338, 204, 242, 424, 175, 72, 199, 294, 103, 454, 275, 66, 179, 401, 256, 279, 222, 359, 84, 405, 177, 319, 374, 245, 210, 245, 362, 79, 163, 140, 375, 326, 332, 291, 362, 243, 370, 92, 81, 192, 284, 374, 377, 317, 170, 187, 362, 297, 192, 310
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