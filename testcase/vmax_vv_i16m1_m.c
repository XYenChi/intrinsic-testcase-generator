/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    67, 31621, 53771, 8608, 45548, 8917, 21499, 32302, 44528, 37362, 56828, 34275, 20373, 19228, 11554, 22
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    49677, 18931, 58573, 25246, 46285, 33089, 34378, 40995, 12232, 55818, 26955, 57934, 64730, 21, 40524, 64860
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    42414, 46907, 5812, 11863, 61344, 47923, 57905, 3229, 26282, 20877, 18951, 58096, 28072, 56798, 43310, 40506
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    42414, 46907, 58573, 11863, 61344, 33089, 34378, 3229, 44528, 55818, 56828, 57934, 28072, 56798, 43310, 64860
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
