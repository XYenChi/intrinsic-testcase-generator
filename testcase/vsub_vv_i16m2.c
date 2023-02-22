/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    98, 114, 235, 172, 145, 81, 252, 184, 31, 50, 164, 67, 70, 113, 4, 81, 156, 212, 181, 128, 56, 49, 193, 202, 239, 180, 172, 127, 92, 120, 23, 3, 75, 132, 208, 166, 120, 231, 135, 150, 17, 237, 25, 129, 2, 99, 149, 151, 44, 49, 49, 147, 49, 255, 255, 84, 148, 56, 254, 191, 235, 239, 42, 78
    };
    const int *in1 = &data1[0];
    int data2[] = {
    201, 134, 144, 154, 115, 225, 84, 194, 12, 135, 254, 23, 150, 188, 86, 75, 117, 190, 52, 175, 196, 46, 162, 231, 244, 53, 4, 85, 47, 240, 12, 217, 41, 185, 36, 57, 96, 167, 6, 109, 125, 142, 63, 240, 207, 159, 174, 130, 149, 102, 222, 118, 158, 64, 85, 75, 27, 28, 166, 86, 51, 229, 41, 160
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m2_t out = __riscv_vsub_vv_i16m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
  }
   int golden[] = {
   -103, -20, 91, 18, 30, -144, 168, -10, 19, -85, -90, 44, -80, -75, -82, 6, 39, 22, 129, -47, -140, 3, 31, -29, -5, 127, 168, 42, 45, -120, 11, -214, 34, -53, 172, 109, 24, 64, 129, 41, -108, 95, -38, -111, -205, -60, -25, 21, -105, -53, -173, 29, -109, 191, 170, 9, 121, 28, 88, 105, 184, 10, 1, -82
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