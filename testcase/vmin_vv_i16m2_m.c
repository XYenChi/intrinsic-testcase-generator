/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    49912, 32493, 42959, 23175, 28182, 27187, 57684, 14355, 22244, 54526, 23286, 53206, 25542, 29507, 57076, 42369
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    33556, 17383, 40911, 25330, 55529, 43650, 59543, 63211, 9920, 44374, 47361, 43868, 21313, 53442, 2430, 38162
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    23164, 30642, 61323, 19205, 40171, 57281, 40270, 62408, 26036, 11822, 62790, 30317, 16057, 3977, 52083, 39778
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    49912, 30642, 61323, 19205, 40171, 43650, 59543, 63211, 26036, 54526, 62790, 53206, 16057, 53442, 57076, 39778
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
