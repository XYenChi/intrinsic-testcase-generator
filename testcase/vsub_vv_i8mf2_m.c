/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    142, 81, 244, 239, 47, 24, 241, 245, 133, 80, 215, 12, 6, 206, 107, 112, 55, 187, 184, 238, 202, 153, 85, 100, 138, 210, 70, 83, 224, 76, 119, 34, 17, 86, 17, 163, 142, 243, 101, 4, 186, 47, 54, 232, 106, 208, 245, 27, 236, 85, 5, 40, 53, 61, 117, 85, 118, 47, 49, 89, 191, 115, 62, 163
    };
    const int *in1 = &data1[0];
    int data2[] = {
    93, 133, 78, 4, 118, 105, 72, 89, 112, 148, 193, 111, 234, 66, 46, 90, 194, 198, 142, 132, 253, 208, 117, 88, 147, 142, 109, 17, 93, 15, 73, 174, 38, 227, 104, 199, 165, 155, 191, 251, 155, 219, 70, 199, 235, 178, 48, 245, 134, 147, 253, 25, 94, 146, 121, 201, 89, 241, 242, 225, 179, 84, 99, 142
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    int masked[] = {
    1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf2_t out = __riscv_vsub_vv_i8mf2_m (mask, data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
   int golden[] = {
   49, -52, 166, 235, -71, -81, 169, 156, 21, -68, 22, -99, -228, 140, 61, 22, -139, -11, 42, 106, -51, -55, -32, 12, -9, 68, -39, 66, 131, 61, 46, -140, -21, -141, -87, -36, -23, 88, -90, -247, 31, -172, -16, 33, -129, 30, 197, -218, 102, -62, -248, 15, -41, -85, -4, -116, 29, -194, -193, -136, 12, 31, -37, 21
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
