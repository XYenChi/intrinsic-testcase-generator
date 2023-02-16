/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    214, 225, 105, 42, 107, 118, 143, 25, 14, 66, 194, 58, 166, 34, 224, 33, 215, 192, 180, 255, 60, 67, 169, 82, 10, 139, 253, 14, 198, 92, 66, 33, 212, 233, 57, 210, 211, 138, 17, 102, 155, 66, 202, 19, 244, 111, 94, 154, 27, 66, 77, 158, 187, 55, 223, 6, 181, 211, 63, 213, 121, 202, 68, 38
    };
    const int *in1 = &data1[0];
    int data2[] = {
    65, 159, 161, 137, 242, 219, 115, 178, 16, 238, 105, 48, 147, 174, 177, 148, 220, 241, 58, 83, 125, 147, 118, 64, 69, 78, 83, 218, 51, 170, 168, 126, 79, 191, 26, 247, 169, 239, 211, 69, 57, 49, 238, 48, 78, 158, 140, 181, 191, 141, 46, 223, 189, 188, 81, 37, 87, 64, 58, 191, 188, 179, 33, 22
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32m2_t out = __riscv_vsub_vx_i32m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
  }
   int golden[] = {
   149, 66, -56, -95, -135, -101, 28, -153, -2, -172, 89, 10, 19, -140, 47, -115, -5, -49, 122, 172, -65, -80, 51, 18, -59, 61, 170, -204, 147, -78, -102, -93, 133, 42, 31, -37, 42, -101, -194, 33, 98, 17, -36, -29, 166, -47, -46, -27, -164, -75, 31, -65, -2, -133, 142, -31, 94, 147, 5, 22, -67, 23, 35, 16
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
