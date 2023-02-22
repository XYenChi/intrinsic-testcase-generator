/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    163, 76, 172, 135, 176, 255, 184, 56, 231, 79, 87, 22, 124, 94, 33, 205, 183, 92, 117, 239, 175, 87, 162, 97, 136, 173, 93, 140, 118, 42, 169, 146, 63, 8, 101, 135, 182, 175, 82, 163, 15, 119, 196, 171, 7, 50, 69, 221, 150, 176, 156, 52, 71, 232, 153, 107, 77, 212, 26, 160, 83, 193, 65, 109
    };
    const int *in1 = &data1[0];
    int data2[] = {
    39, 248, 107, 153, 61, 114, 192, 93, 45, 196, 39, 129, 2, 121, 160, 115, 107, 80, 196, 249, 72, 178, 146, 51, 34, 135, 80, 228, 203, 200, 236, 224, 154, 196, 240, 15, 115, 182, 89, 50, 195, 170, 183, 170, 14, 28, 32, 149, 168, 178, 130, 199, 156, 128, 77, 193, 207, 37, 122, 81, 211, 209, 134, 249
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf8_t out = __riscv_vsub_vv_i8mf8 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
  }
   int golden[] = {
   124, -172, 65, -18, 115, 141, -8, -37, 186, -117, 48, -107, 122, -27, -127, 90, 76, 12, -79, -10, 103, -91, 16, 46, 102, 38, 13, -88, -85, -158, -67, -78, -91, -188, -139, 120, 67, -7, -7, 113, -180, -51, 13, 1, -7, 22, 37, 72, -18, -2, 26, -147, -85, 104, 76, -86, -130, 175, -96, 79, -128, -16, -69, -140
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