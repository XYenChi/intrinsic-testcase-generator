/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    152, 147, 49, 223, 138, 219, 203, 155, 210, 248, 59, 178, 60, 65, 191, 58, 177, 172, 157, 20, 129, 17, 188, 39, 224, 124, 41, 115, 56, 176, 31, 186, 14, 200, 121, 30, 105, 42, 58, 23, 248, 156, 252, 114, 181, 208, 76, 224, 224, 28, 231, 48, 140, 235, 149, 24, 196, 140, 153, 101, 215, 153, 99, 76
    };
    const int *in1 = &data1[0];
    int data2[] = {
    189, 130, 208, 14, 163, 91, 88, 195, 155, 3, 144, 45, 1, 176, 4, 177, 157, 37, 78, 197, 138, 221, 72, 58, 143, 229, 238, 155, 160, 222, 140, 197, 80, 190, 57, 249, 14, 233, 215, 228, 88, 35, 212, 20, 7, 224, 226, 7, 203, 193, 142, 192, 165, 250, 237, 205, 30, 35, 252, 125, 149, 234, 5, 93
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    int masked[] = {
    1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m1_t out = __riscv_vsub_vx_i8m1_m (mask, data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
   int golden[] = {
   -37, 17, -159, 209, -25, 128, 115, -40, 55, 245, -85, 133, 59, -111, 187, -119, 20, 135, 79, -177, -9, -204, 116, -19, 81, -105, -197, -40, -104, -46, -109, -11, -66, 10, 64, -219, 91, -191, -157, -205, 160, 121, 40, 94, 174, -16, -150, 217, 21, -165, 89, -144, -25, -15, -88, -181, 166, 105, -99, -24, 66, -81, 94, -17
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
