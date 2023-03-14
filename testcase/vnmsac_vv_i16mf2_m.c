/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -46, 84, 117, 46, 118, 38, 116, -59, 113, -89, -96, -76, 5, 32, 55, -98
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    0, -25, -91, 84, 31, 101, -39, -82, -9, 41, -31, 94, 122, 38, 116, -64
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const int out_data[] = {
    0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1
    };
    const int16_t *out = &out_data[0];
    uint32_t masked[] = {
    1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1
    };
    const uint32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vv_i16mf2_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf2 (bool16_t mask, int16_t *out, vint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    0, 1, 1, 0, 1, 61698, 4524, 1, 1018, 3650, 62560, 0, 64926, 1, 0, 59265
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
