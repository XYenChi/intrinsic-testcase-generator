/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    131, 144, 16, 208, 162, 192, 168, 211, 82, 100, 77, 157, 246, 137, 186, 63, 102, 45, 253, 220, 139, 56, 206, 145, 2, 131, 85, 2, 96, 57, 61, 175, 64, 52, 1, 92, 40, 194, 243, 140, 189, 9, 188, 220, 166, 42, 20, 37, 128, 149, 62, 237, 228, 236, 207, 153, 230, 99, 86, 169, 68, 88, 23, 117
    };
    const int *in1 = &data1[0];
    int data2[] = {
    51, 146, 168, 54, 71, 138, 153, 41, 20, 4, 210, 228, 152, 215, 17, 218, 147, 124, 154, 251, 71, 30, 152, 96, 98, 227, 46, 95, 59, 202, 184, 195, 238, 75, 239, 40, 191, 32, 167, 1, 104, 11, 98, 67, 189, 168, 194, 176, 232, 81, 120, 69, 237, 64, 155, 63, 174, 66, 80, 176, 233, 117, 41, 253
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    int masked[] = {
    0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16mf2_t out = __riscv_vsub_vv_i16mf2_m (mask, data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
   int golden[] = {
   80, -2, -152, 154, 91, 54, 15, 170, 62, 96, -133, -71, 94, -78, 169, -155, -45, -79, 99, -31, 68, 26, 54, 49, -96, -96, 39, -93, 37, -145, -123, -20, -174, -23, -238, 52, -151, 162, 76, 139, 85, -2, 90, 153, -23, -126, -174, -139, -104, 68, -58, 168, -9, 172, 52, 90, 56, 33, 6, -7, -165, -29, -18, -136
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
