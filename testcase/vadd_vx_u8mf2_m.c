/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -61, 96, -108, 13, 56, -70, 11, -96, -42, -101, 40, -6, -87, -7, -5, -71
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -40, 42, -23, -4, 68, 105, -20, -1, 4, -68, -25, 117, -18, 8, 50, -32
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    const int out_data[] = {
    -39, -70, -50, 127, 16, 124, 71, 115, 118, 101, 71, -124, -46, 105, -23, 36
    };
    const int8_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2_m (mask, *in2, vl);
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u8mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf2 (bool8_t mask, int8_t *out, vint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -39, -69, -50, 127, 17, 124, 72, 115, 118, 102, 72, -123, -46, 105, -22, 36
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
