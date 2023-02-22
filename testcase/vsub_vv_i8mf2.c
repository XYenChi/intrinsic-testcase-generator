/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    246, 203, 210, 178, 215, 93, 43, 15, 56, 76, 149, 255, 165, 196, 93, 200, 14, 124, 216, 152, 90, 151, 139, 212, 122, 233, 240, 193, 151, 113, 21, 28, 188, 34, 58, 252, 88, 99, 191, 253, 216, 94, 243, 123, 236, 168, 92, 238, 168, 84, 82, 182, 101, 187, 163, 56, 199, 148, 15, 15, 40, 7, 9, 226
    };
    const int *in1 = &data1[0];
    int data2[] = {
    112, 158, 230, 254, 161, 192, 4, 247, 198, 14, 109, 147, 46, 135, 108, 112, 64, 101, 238, 184, 206, 137, 105, 26, 162, 232, 158, 48, 201, 144, 109, 46, 205, 212, 71, 156, 131, 250, 100, 224, 200, 24, 92, 31, 248, 107, 165, 154, 213, 250, 248, 87, 29, 234, 77, 32, 192, 41, 150, 40, 195, 217, 235, 138
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf2_t out = __riscv_vsub_vv_i8mf2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
  }
   int golden[] = {
   134, 45, -20, -76, 54, -99, 39, -232, -142, 62, 40, 108, 119, 61, -15, 88, -50, 23, -22, -32, -116, 14, 34, 186, -40, 1, 82, 145, -50, -31, -88, -18, -17, -178, -13, 96, -43, -151, 91, 29, 16, 70, 151, 92, -12, 61, -73, 84, -45, -166, -166, 95, 72, -47, 86, 24, 7, 107, -135, -25, -155, -210, -226, 88
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