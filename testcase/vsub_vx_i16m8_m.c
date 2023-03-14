/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    31, 86, 56, 11, 23, 94, 13, -82, -33, 116, -22, -24, -35, 68, 94, -28
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -124, 71, -46, -107, 22, -34, -59, -26, 31, -8, -71, 8, 10, -116, -61, 0
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const int out_data[] = {
    1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1
    };
    const int16_t *out = &out_data[0];
    uint2_t masked[] = {
    0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1
    };
    const uint2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_i16m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m8 (bool16_t mask, int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    1, 15, 0, 118, 1, 1, 0, 1, 1, 1, 49, 65504, 0, 184, 155, 65508
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
