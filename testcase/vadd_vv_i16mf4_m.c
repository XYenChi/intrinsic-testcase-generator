/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    132, 118, 221, 34, 6, 245, 72, 34, 245, 52, 38, 116, 205, 253, 145, 104
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    89, 239, 37, 86, 216, 202, 232, 100, 222, 73, 209, 91, 62, 97, 10, 131
    };
    const int16_t *in2 = &data2[0];
    const int out_data[] = {
    25, 82, 69, 85, 124, 188, 40, 66, 128, 59, 182, 56, 138, 110, 120, 24
    };
    int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint16mf4_t out_data = __riscv_vadd_vv_i16mf4_m (mask, data1, data2, vl)
        vint16mf4_t __riscv_vse16_v_i16mf4 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    221, 357, 69, 120, 124, 188, 40, 66, 467, 59, 182, 56, 267, 350, 155, 24
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
