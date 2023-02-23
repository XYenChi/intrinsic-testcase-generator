/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    82, 149, 59, 19, 215, 28, 10, 31, 64, 246, 255, 175, 244, 9, 202, 99
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    57, 108, 196, 229, 26, 116, 166, 178, 230, 39, 155, 158, 171, 141, 162, 93
    };
    const int16_t *in2 = &data2[0];
    const int out_data[] = {
    11, 49, 36, 224, 197, 151, 50, 226, 4, 120, 38, 102, 19, 179, 105, 90
    };
    int16_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint16m8_t out_data = __riscv_vadd_vv_i16m8_m (mask, data1, data2, vl)
        vint16m8_t __riscv_vse16_v_i16m8 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    139, 49, 255, 248, 241, 151, 176, 209, 294, 120, 410, 102, 19, 150, 364, 90
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
