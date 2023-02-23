/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    244, 143, 146, 238, 167, 33, 110, 211, 4, 247, 80, 129, 178, 207, 18, 235
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    181, 107, 121, 54, 64, 57, 131, 249, 135, 176, 205, 232, 249, 255, 143, 255
    };
    const int64_t *in2 = &data2[0];
    const int out_data[] = {
    97, 41, 59, 238, 121, 241, 52, 213, 87, 233, 243, 65, 129, 233, 60, 101
    };
    int64_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint64m8_t out_data = __riscv_vadd_vx_i64m8_m (mask, data1, data2, vl)
        vint64m8_t __riscv_vse64_v_i64m8 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    425, 250, 267, 292, 121, 90, 241, 460, 87, 423, 243, 361, 427, 233, 161, 490
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
