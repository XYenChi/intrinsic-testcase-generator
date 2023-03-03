/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    21382, 16728, 39474, 11634, 42164, 4050, 60234, 11237, 26746, 64293, 25147, 5090, 13958, 49921, 31022, 39577
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    63153, 30417, 12810, 35345, 55647, 43171, 57339, 59934, 3689, 23132, 7448, 26540, 32469, 42353, 51441, 33416
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    51704, 55269, 22670, 51328, 31345, 37795, 29176, 9604, 23130, 526, 54447, 56133, 35761, 55036, 14880, 43664
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    51704, 508815576, 22670, 51328, 2346300108, 37795, 29176, 9604, 23130, 1487225676, 54447, 135088600, 35761, 55036, 14880, 43664
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
