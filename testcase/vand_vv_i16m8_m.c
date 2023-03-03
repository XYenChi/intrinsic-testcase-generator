/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    4383, 18246, 55061, 33538, 44402, 30448, 63765, 8652, 15198, 44931, 65312, 4779, 21826, 25751, 46870, 58019
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    54412, 13528, 2124, 28708, 47208, 41554, 52137, 39286, 23680, 16937, 64850, 51781, 24271, 38342, 32271, 9269
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    54002, 46005, 6188, 57641, 18478, 22966, 41582, 35799, 22795, 38058, 47468, 48403, 42500, 5162, 43499, 42179
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    54002, 46005, 2124, 28708, 47208, 22966, 52137, 39286, 22795, 38058, 64850, 48403, 24271, 5162, 43499, 42179
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
