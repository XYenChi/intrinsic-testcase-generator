/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    1594, 28391, 54611, 50276, 42511, 31083, 64252, 63499, 19099, 14488, 40179, 58904, 1787, 47684, 42977, 13352
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    29120, 9936, 16411, 37215, 33262, 59851, 58055, 47991, 19040, 22992, 33552, 7462, 11274, 60557, 25423, 61529
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    52339, 39412, 40011, 19502, 5363, 65063, 52643, 6733, 41124, 4490, 31165, 41413, 12321, 50250, 7272, 11031
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    30715, 38328, 71023, 87492, 75774, 90935, 122307, 111491, 38140, 37481, 73732, 66366, 13062, 108241, 68401, 74882
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
