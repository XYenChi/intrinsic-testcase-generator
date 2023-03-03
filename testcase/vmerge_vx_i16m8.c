/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    26774, 55485, 16672, 55391, 2255, 54601, 36211, 56194, 6763, 11206, 23463, 15417, 59808, 64110, 19371, 33729
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    48754, 21717, 4574, 20801, 20963, 16973, 62929, 37690, 13279, 31442, 13646, 62064, 47927, 8201, 18941, 10106
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    bool2_t masked[] = {
    0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8 (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i16m8 (data1_v, data2_v, size_t vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    26774, 21717, 4574, 55391, 2255, 16973, 36211, 37690, 13279, 11206, 13646, 15417, 59808, 64110, 18941, 33729
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
