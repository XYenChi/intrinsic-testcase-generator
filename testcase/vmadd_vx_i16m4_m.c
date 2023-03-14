/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    83, 55, 14, 96, -33, 97, -78, -120, 80, -61, -108, -51, 95, -98, -109, 56
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    18, 59, 23, -18, -106, -27, 89, -16, 25, 86, 107, -55, -81, 25, -70, 110
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const int out_data[] = {
    0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0
    };
    const int16_t *out = &out_data[0];
    uint4_t masked[] = {
    1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1
    };
    const uint4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, in2, vl);
    vint16m4_t out_v = __riscv_vle16_v_i16m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmadd_vx_i16m4_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m4 (bool16_t mask, int16_t *out, vint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    18, 114, 37, 96, 65430, 65509, 65458, 65416, 80, 25, 65428, 65430, 95, 25, 65466, 110
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
