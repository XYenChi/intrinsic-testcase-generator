/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -39, -128, -52, -5, 44, -36, 91, -69, -96, 25, -55, 33, 50, 24, 101, -106
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -120, 127, -102, 105, 118, 29, -88, 68, -42, -96, 118, -120, -80, 81, 68, 24
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    const int out_data[] = {
    28, 89, -30, -120, -67, 112, -101, 77, 94, -46, 60, 98, 87, -126, -55, -74
    };
    const int8_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, *in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4_m (mask, *in2, vl);
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i8mf4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf4 (bool8_t mask, int8_t *out, vint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    29, 89, -30, -120, -66, 113, -100, 77, 95, -46, 61, 98, 87, -125, -54, -73
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
