/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    108, 149, 22, 206, 32, 113, 118, 133, 40, 227, 193, 114, 151, 181, 242, 221, 190, 188, 218, 248, 141, 236, 50, 214, 188, 117, 249, 194, 10, 66, 207, 82, 155, 248, 98, 244, 220, 107, 12, 247, 219, 103, 191, 153, 118, 76, 241, 251, 61, 42, 94, 210, 9, 221, 33, 68, 231, 99, 217, 189, 47, 248, 116, 117
    };
    const int *in1 = &data1[0];
    int data2[] = {
    150, 184, 180, 27, 240, 73, 232, 173, 15, 55, 15, 185, 104, 233, 227, 163, 198, 38, 23, 246, 35, 98, 86, 59, 223, 22, 56, 152, 105, 76, 156, 186, 171, 1, 146, 81, 69, 30, 159, 74, 235, 176, 8, 134, 146, 167, 117, 249, 18, 65, 73, 26, 206, 99, 197, 171, 92, 81, 13, 45, 79, 0, 146, 177
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    int masked[] = {
    0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m4_t out = __riscv_vsub_vx_i8m4_m (mask, data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
   int golden[] = {
   -42, -35, -158, 179, -208, 40, -114, -40, 25, 172, 178, -71, 47, -52, 15, 58, -8, 150, 195, 2, 106, 138, -36, 155, -35, 95, 193, 42, -95, -10, 51, -104, -16, 247, -48, 163, 151, 77, -147, 173, -16, -73, 183, 19, -28, -91, 124, 2, 43, -23, 21, 184, -197, 122, -164, -103, 139, 18, 204, 144, -32, 248, -30, -60
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
