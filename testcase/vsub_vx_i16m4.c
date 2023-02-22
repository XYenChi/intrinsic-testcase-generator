/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    137, 141, 243, 157, 64, 246, 133, 183, 112, 49, 23, 174, 142, 44, 82, 15, 155, 127, 69, 33, 198, 143, 121, 9, 127, 89, 110, 107, 156, 249, 119, 35, 217, 109, 79, 228, 128, 38, 57, 247, 86, 219, 2, 228, 58, 176, 97, 86, 102, 8, 116, 5, 171, 79, 143, 231, 210, 103, 223, 221, 205, 123, 178, 27
    };
    const int *in1 = &data1[0];
    int data2[] = {
    206, 147, 167, 136, 186, 40, 248, 140, 226, 54, 97, 85, 34, 37, 217, 53, 225, 154, 131, 58, 151, 197, 252, 165, 130, 248, 86, 20, 107, 9, 212, 133, 75, 18, 133, 125, 191, 238, 52, 199, 80, 210, 109, 2, 225, 253, 157, 109, 196, 111, 118, 195, 171, 141, 123, 120, 15, 174, 157, 84, 38, 43, 201, 59
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m4_t out = __riscv_vsub_vx_i16m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
  }
   int golden[] = {
   -69, -6, 76, 21, -122, 206, -115, 43, -114, -5, -74, 89, 108, 7, -135, -38, -70, -27, -62, -25, 47, -54, -131, -156, -3, -159, 24, 87, 49, 240, -93, -98, 142, 91, -54, 103, -63, -200, 5, 48, 6, 9, -107, 226, -167, -77, -60, -23, -94, -103, -2, -190, 0, -62, 20, 111, 195, -71, 66, 137, 167, 80, -23, -32
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