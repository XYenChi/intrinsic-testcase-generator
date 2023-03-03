/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    55887, 26, 4606, 30211, 7828, 14261, 33523, 54227, 13545, 6995, 9421, 7011, 5592, 26808, 57817, 18081
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    46179, 1391, 55739, 48115, 29727, 37306, 34814, 26435, 37307, 46960, 53916, 56759, 15966, 55036, 4341, 32457
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    57631, 47711, 20223, 11124, 35106, 54671, 41679, 35902, 40020, 36375, 2923, 37379, 61865, 31475, 8092, 13142
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    9708, -1365, -51134, -17904, -21899, -23045, -1291, 27791, -23762, -39965, -44495, -49749, -10375, -28229, 53475, -14377
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
