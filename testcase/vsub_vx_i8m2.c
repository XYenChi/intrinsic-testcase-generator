/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    164, 82, 13, 94, 245, 177, 22, 104, 77, 159, 94, 91, 111, 83, 198, 57, 135, 24, 101, 13, 2, 157, 172, 230, 125, 250, 123, 236, 241, 106, 36, 108, 180, 131, 151, 172, 231, 105, 146, 46, 5, 72, 8, 232, 100, 13, 177, 184, 66, 169, 222, 175, 17, 162, 251, 18, 6, 194, 197, 201, 207, 2, 144, 64
    };
    const int *in1 = &data1[0];
    int data2[] = {
    163, 84, 108, 120, 234, 44, 203, 81, 129, 7, 206, 116, 12, 97, 229, 125, 242, 62, 252, 216, 110, 58, 73, 2, 155, 34, 162, 83, 116, 171, 28, 16, 38, 116, 156, 127, 147, 93, 177, 20, 47, 121, 156, 133, 38, 132, 213, 229, 59, 69, 45, 192, 106, 1, 196, 172, 248, 25, 140, 167, 177, 61, 13, 62
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m2_t out = __riscv_vsub_vx_i8m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
  }
   int golden[] = {
   1, -2, -95, -26, 11, 133, -181, 23, -52, 152, -112, -25, 99, -14, -31, -68, -107, -38, -151, -203, -108, 99, 99, 228, -30, 216, -39, 153, 125, -65, 8, 92, 142, 15, -5, 45, 84, 12, -31, 26, -42, -49, -148, 99, 62, -119, -36, -45, 7, 100, 177, -17, -89, 161, 55, -154, -242, 169, 57, 34, 30, -59, 131, 2
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