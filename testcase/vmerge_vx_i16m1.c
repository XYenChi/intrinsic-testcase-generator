/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    54517, 10865, 33965, 16470, 39275, 38598, 64381, 18079, 16089, 28638, 63735, 15460, 24664, 25684, 8010, 35523
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    35471, 61522, 41421, 45341, 26558, 20813, 1667, 61683, 49796, 8989, 22161, 15306, 13581, 14401, 34893, 52142
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    bool16_t masked[] = {
    0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1 (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i16m1 (data1_v, data2_v, size_t vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    54517, 10865, 41421, 16470, 26558, 38598, 1667, 18079, 16089, 28638, 63735, 15306, 24664, 14401, 8010, 52142
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
