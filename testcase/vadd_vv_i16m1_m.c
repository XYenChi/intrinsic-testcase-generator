/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    29, 169, 31, 170, 42, 20, 56, 163, 48, 185, 166, 214, 6, 154, 67, 68
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    96, 38, 9, 164, 95, 127, 96, 45, 175, 149, 48, 173, 161, 104, 233, 113
    };
    const int16_t *in2 = &data2[0];
    const int out_data[] = {
    89, 160, 125, 196, 132, 117, 0, 11, 3, 41, 77, 11, 231, 0, 31, 166
    };
    int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint16m1_t out_data = __riscv_vadd_vv_i16m1_m (mask, data1, data2, vl)
        vint16m1_t __riscv_vse16_v_i16m1 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    125, 207, 40, 196, 137, 147, 152, 208, 223, 41, 214, 387, 231, 0, 300, 181
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
