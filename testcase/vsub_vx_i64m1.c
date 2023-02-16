/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    87, 124, 43, 32, 116, 23, 11, 165, 44, 235, 6, 4, 183, 229, 14, 195, 203, 1, 213, 144, 106, 215, 115, 191, 101, 152, 95, 146, 105, 134, 177, 10, 211, 49, 84, 49, 16, 86, 249, 65, 191, 127, 137, 232, 33, 93, 196, 8, 165, 94, 5, 15, 89, 247, 85, 155, 52, 128, 187, 11, 201, 87, 85, 247
    };
    const int *in1 = &data1[0];
    int data2[] = {
    76, 54, 11, 78, 213, 229, 37, 7, 141, 88, 10, 96, 73, 25, 144, 159, 50, 45, 51, 57, 31, 210, 59, 41, 187, 76, 22, 59, 58, 124, 62, 89, 139, 154, 223, 29, 131, 109, 202, 95, 160, 137, 147, 255, 168, 64, 25, 200, 241, 141, 12, 148, 136, 246, 113, 239, 24, 212, 48, 97, 149, 134, 89, 198
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint64m1_t out = __riscv_vsub_vx_i64m1 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
  }
   int golden[] = {
   11, 70, 32, -46, -97, -206, -26, 158, -97, 147, -4, -92, 110, 204, -130, 36, 153, -44, 162, 87, 75, 5, 56, 150, -86, 76, 73, 87, 47, 10, 115, -79, 72, -105, -139, 20, -115, -23, 47, -30, 31, -10, -10, -23, -135, 29, 171, -192, -76, -47, -7, -133, -47, 1, -28, -84, 28, -84, 139, -86, 52, -47, -4, 49
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
