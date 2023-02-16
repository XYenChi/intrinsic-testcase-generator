/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    230, 28, 46, 173, 136, 29, 238, 116, 60, 25, 105, 87, 236, 247, 89, 13, 15, 43, 145, 250, 160, 62, 188, 77, 191, 218, 246, 62, 79, 255, 230, 159, 50, 184, 134, 17, 91, 168, 254, 200, 247, 246, 231, 83, 84, 137, 30, 9, 69, 10, 151, 13, 141, 171, 3, 80, 104, 156, 25, 166, 121, 159, 167, 198
    };
    const int *in1 = &data1[0];
    int data2[] = {
    35, 232, 8, 207, 36, 192, 235, 28, 25, 203, 92, 65, 202, 53, 0, 100, 127, 247, 138, 2, 209, 46, 199, 10, 141, 182, 221, 72, 26, 91, 129, 44, 92, 6, 56, 58, 206, 105, 127, 117, 241, 77, 151, 7, 79, 174, 131, 93, 16, 31, 219, 171, 3, 110, 218, 59, 22, 88, 51, 29, 74, 177, 116, 4
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32m4_t out = __riscv_vsub_vx_i32m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
  }
   int golden[] = {
   195, -204, 38, -34, 100, -163, 3, 88, 35, -178, 13, 22, 34, 194, 89, -87, -112, -204, 7, 248, -49, 16, -11, 67, 50, 36, 25, -10, 53, 164, 101, 115, -42, 178, 78, -41, -115, 63, 127, 83, 6, 169, 80, 76, 5, -37, -101, -84, 53, -21, -68, -158, 138, 61, -215, 21, 82, 68, -26, 137, 47, -18, 51, 194
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
