/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    119, 141, 110, 187, 81, 164, 167, 10, 245, 218, 1, 255, 53, 164, 90, 1, 67, 102, 69, 190, 215, 255, 52, 28, 25, 36, 60, 26, 204, 89, 107, 78, 196, 11, 159, 115, 91, 97, 120, 87, 25, 250, 76, 62, 223, 39, 212, 18, 70, 88, 191, 60, 22, 5, 243, 236, 194, 150, 48, 16, 35, 228, 49, 164
    };
    const int *in1 = &data1[0];
    int data2[] = {
    212, 139, 138, 205, 226, 143, 167, 141, 11, 143, 184, 185, 172, 100, 249, 55, 240, 202, 40, 76, 187, 245, 83, 183, 148, 12, 119, 208, 7, 238, 160, 67, 57, 57, 108, 82, 240, 151, 96, 93, 141, 4, 62, 212, 26, 54, 79, 11, 111, 70, 99, 16, 81, 124, 224, 249, 3, 48, 248, 90, 129, 154, 79, 56
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint64m4_t out = __riscv_vsub_vx_i64m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
  }
   int golden[] = {
   -93, 2, -28, -18, -145, 21, 0, -131, 234, 75, -183, 70, -119, 64, -159, -54, -173, -100, 29, 114, 28, 10, -31, -155, -123, 24, -59, -182, 197, -149, -53, 11, 139, -46, 51, 33, -149, -54, 24, -6, -116, 246, 14, -150, 197, -15, 133, 7, -41, 18, 92, 44, -59, -119, 19, -13, 191, 102, -200, -74, -94, 74, -30, 108
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