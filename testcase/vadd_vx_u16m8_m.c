/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -19690, -27507, -4407, 18810, 17921, 16373, -21619, 22799, 4693, -2389, -4509, -15504, -31077, 15257, 4124, -21157
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -9634, -30844, -24494, -11384, 10451, -16302, -3658, -9707, 2367, 1, 16874, 26467, -21785, -21614, -20308, 11823
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const int out_data[] = {
    17424, -5280, 21881, -25386, -27003, 19884, -5981, 18100, -28344, 1079, -6627, -10788, 8528, -7298, 18759, -3815
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u16m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m8 (bool16_t mask, int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    17424, -5280, 21881, -25386, -27003, 19885, -5980, 18100, -28344, 1080, -6626, -10788, 8529, -7298, 18760, -3815
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
