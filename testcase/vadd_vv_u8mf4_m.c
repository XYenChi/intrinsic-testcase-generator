/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    123, 71, 46, -43, -55, 28, 108, -103, 116, 16, -76, -39, -100, -97, 34, -42
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    1, 38, -124, 46, 5, -12, 124, 47, 85, 57, 105, -96, -60, 32, 127, -106
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    const int out_data[] = {
    -67, 47, -76, 61, -30, -7, 110, -56, 32, 61, 37, 48, 39, 51, 36, -76
    };
    const int8_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, *in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4_m (mask, *in2, vl);
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u8mf4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf4 (bool8_t mask, int8_t *out, vint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -66, 47, -75, 62, -29, -7, 110, -55, 33, 61, 37, 48, 39, 51, 37, -76
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
