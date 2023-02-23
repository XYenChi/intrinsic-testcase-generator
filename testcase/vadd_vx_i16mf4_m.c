/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    172, 17, 124, 158, 135, 108, 177, 196, 70, 112, 39, 252, 53, 110, 130, 124
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    162, 141, 197, 246, 220, 167, 123, 18, 251, 122, 8, 61, 40, 157, 6, 81
    };
    const int16_t *in2 = &data2[0];
    const int out_data[] = {
    204, 143, 148, 4, 26, 161, 172, 209, 104, 19, 34, 248, 1, 65, 64, 160
    };
    int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint16mf4_t out_data = __riscv_vadd_vx_i16mf4_m (mask, data1, data2, vl)
        vint16mf4_t __riscv_vse16_v_i16mf4 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    204, 158, 148, 4, 355, 275, 172, 214, 321, 19, 34, 313, 1, 267, 64, 205
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
