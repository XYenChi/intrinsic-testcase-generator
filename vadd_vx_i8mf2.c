/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <riscv_vector.h>
int main(){
    int data1[] = {
  81, 236, 237, 156, 191, 238, 255, 235, 166, 167, 243, 249, 4, 131, 80, 197, 150, 99, 63, 64, 11, 36, 93, 120, 61, 211, 222, 3, 226, 80, 45, 116, 39, 220, 81, 226, 73, 251, 178, 202, 51, 156, 48, 251, 60, 163, 230, 186, 2, 52, 188, 137, 89, 6, 168, 53, 230, 92, 49, 27, 67, 143, 59, 244
  };
  const int *in1 = &data1[0];
    int data2[] = {
  253, 57, 180, 51, 203, 225, 20, 75, 218, 186, 62, 253, 222, 184, 10, 196, 97, 45, 41, 45, 135, 81, 253, 93, 141, 201, 115, 175, 141, 215, 129, 215, 178, 86, 29, 98, 181, 174, 94, 225, 79, 243, 124, 144, 126, 23, 240, 25, 113, 22, 39, 71, 180, 209, 121, 1, 71, 38, 175, 44, 134, 195, 149, 2
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint8mf2_t out = __riscv_vadd_vx_i8mf2 (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  334, 293, 417, 207, 394, 463, 275, 310, 384, 353, 305, 502, 226, 315, 90, 393, 247, 144, 104, 109, 146, 117, 346, 213, 202, 412, 337, 178, 367, 295, 174, 331, 217, 306, 110, 324, 254, 425, 272, 427, 130, 399, 172, 395, 186, 186, 470, 211, 115, 74, 227, 208, 269, 215, 289, 54, 301, 130, 224, 71, 201, 338, 208, 246
  };
  int fail = 0;
  for (int i = 0; i < 64; ++i)
     if (golden0[i] != out0_data[i]) {
       printf ("idx=%d golden=%d out=%d\n", i, golden0[i], out0[i]);
       fail++;
     }
  if (fail) {
    printf("FAIL\n");
    return 1;
  } else {
    printf("PASS\n");
    return 0;
  }
}
