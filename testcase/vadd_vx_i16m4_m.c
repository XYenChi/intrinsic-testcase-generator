/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    59, 44, 221, 156, 86, 63, 238, 181, 127, 54, 114, 134, 119, 163, 72, 68
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    165, 193, 222, 226, 217, 199, 34, 22, 228, 209, 52, 192, 119, 102, 237, 212
    };
    const int16_t *in2 = &data2[0];
    const int out_data[] = {
    9, 79, 41, 106, 109, 91, 135, 30, 110, 248, 189, 126, 126, 105, 182, 82
    };
    int16_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint16m4_t out_data = __riscv_vadd_vx_i16m4_m (mask, data1, data2, vl)
        vint16m4_t __riscv_vse16_v_i16m4 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    9, 79, 443, 382, 109, 262, 135, 203, 110, 263, 189, 126, 126, 265, 309, 82
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
