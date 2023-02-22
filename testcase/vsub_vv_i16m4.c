/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    141, 25, 61, 185, 147, 242, 54, 251, 184, 152, 113, 245, 163, 94, 38, 198, 245, 46, 203, 135, 218, 210, 1, 40, 106, 137, 138, 89, 168, 188, 137, 229, 25, 231, 135, 144, 167, 174, 44, 89, 196, 155, 11, 104, 180, 161, 212, 86, 229, 80, 159, 123, 61, 202, 162, 56, 98, 117, 163, 134, 124, 84, 227, 127
    };
    const int *in1 = &data1[0];
    int data2[] = {
    139, 109, 197, 32, 38, 113, 191, 254, 75, 18, 130, 116, 182, 202, 220, 31, 249, 120, 40, 29, 34, 173, 40, 215, 173, 109, 127, 190, 171, 186, 45, 146, 211, 212, 14, 192, 101, 110, 134, 54, 2, 191, 21, 199, 140, 15, 91, 149, 171, 208, 61, 149, 220, 63, 239, 160, 127, 21, 59, 188, 217, 39, 234, 145
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m4_t out = __riscv_vsub_vv_i16m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
  }
   int golden[] = {
   2, -84, -136, 153, 109, 129, -137, -3, 109, 134, -17, 129, -19, -108, -182, 167, -4, -74, 163, 106, 184, 37, -39, -175, -67, 28, 11, -101, -3, 2, 92, 83, -186, 19, 121, -48, 66, 64, -90, 35, 194, -36, -10, -95, 40, 146, 121, -63, 58, -128, 98, -26, -159, 139, -77, -104, -29, 96, 104, -54, -93, 45, -7, -18
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