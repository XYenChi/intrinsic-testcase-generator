/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    59332, 55167, 23304, 11799, 25860, 5692, 12717, 55822, 50749, 49290, 14561, 50310, 48074, 31015, 36922, 57580
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    31646, 29011, 15846, 43681, 39650, 49388, 25498, 54769, 47290, 22535, 58785, 52391, 26891, 20290, 8534, 3524
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    48364, 42547, 24250, 45186, 35772, 7330, 14643, 46915, 45812, 24778, 4230, 5553, 16111, 18199, 61150, 45407
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    59332, 42547, 23304, 43681, 39650, 7330, 14643, 46915, 45812, 49290, 4230, 5553, 48074, 31015, 36922, 57580
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
