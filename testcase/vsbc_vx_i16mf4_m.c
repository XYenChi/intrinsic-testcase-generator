/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    58786, 39373, 10970, 64040, 24737, 58488, 49574, 52280, 23660, 62814, 12891, 19226, 9146, 39234, 41835, 3807
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    57606, 56303, 58564, 37194, 18925, 28008, 8810, 17165, 64191, 43342, 48219, 50083, 64054, 31475, 24649, 42354
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    58362, 46095, 34684, 46616, 53631, 27118, 45780, 44252, 41934, 44944, 23498, 44206, 5421, 31015, 57927, 47123
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    1179, -16930, -47595, 26845, 5811, 30480, 40763, 35114, -40531, 19472, -35328, -30857, -54909, 7759, 17186, -38548
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
