/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    59166, 60767, 51709, 20417, 15842, 30673, 10144, 39668, 35863, 41674, 42155, 49391, 13729, 15787, 16141, 55772
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    55095, 36319, 51410, 27448, 55898, 47784, 25279, 54788, 54690, 5765, 47808, 18928, 50033, 15876, 7476, 5050
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    62881, 24516, 17212, 14826, 38253, 50681, 27648, 47381, 35992, 5193, 9413, 29446, 48424, 49054, 36324, 22227
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    62881, 24516, 17212, 27448, 38253, 50681, 27648, 54788, 35992, 41674, 47808, 29446, 48424, 49054, 16141, 55772
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
