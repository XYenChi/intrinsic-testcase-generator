/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    12, 145, 66, 158, 40, 158, 153, 29, 139, 228, 19, 10, 127, 60, 34, 228, 58, 184, 36, 90, 67, 230, 156, 156, 40, 49, 69, 119, 64, 87, 248, 110, 128, 79, 36, 111, 18, 108, 210, 137, 75, 68, 99, 48, 213, 104, 57, 19, 65, 234, 153, 98, 169, 79, 161, 148, 192, 153, 116, 96, 166, 184, 182, 180
    };
    const int *in1 = &data1[0];
    int data2[] = {
    231, 182, 19, 138, 74, 20, 74, 195, 124, 15, 158, 46, 50, 59, 15, 240, 127, 212, 232, 210, 211, 247, 92, 40, 149, 96, 52, 20, 106, 126, 158, 132, 27, 44, 193, 84, 205, 162, 5, 181, 129, 94, 76, 124, 49, 218, 46, 134, 80, 22, 160, 100, 83, 48, 171, 117, 149, 102, 94, 245, 95, 203, 141, 243
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32m8_t out = __riscv_vsub_vx_i32m8 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
  }
   int golden[] = {
   -219, -37, 47, 20, -34, 138, 79, -166, 15, 213, -139, -36, 77, 1, 19, -12, -69, -28, -196, -120, -144, -17, 64, 116, -109, -47, 17, 99, -42, -39, 90, -22, 101, 35, -157, 27, -187, -54, 205, -44, -54, -26, 23, -76, 164, -114, 11, -115, -15, 212, -7, -2, 86, 31, -10, 31, 43, 51, 22, -149, 71, -19, 41, -63
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
