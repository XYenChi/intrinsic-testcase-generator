/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    231, 118, 209, 249, 210, 93, 108, 162, 155, 62, 41, 140, 212, 171, 192, 125
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    132, 127, 15, 181, 224, 97, 82, 2, 66, 175, 254, 163, 41, 124, 94, 210
    };
    const int16_t *in2 = &data2[0];
    const int out_data[] = {
    65, 219, 235, 111, 199, 184, 206, 171, 64, 43, 4, 157, 1, 200, 37, 177
    };
    int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint16m4_t out_data = __riscv_vadd_vv_i16m4_m (mask, data1, data2, vl)
        vint16m4_t __riscv_vse16_v_i16m4 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    363, 219, 224, 111, 434, 184, 190, 171, 221, 43, 295, 157, 1, 295, 286, 335
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
