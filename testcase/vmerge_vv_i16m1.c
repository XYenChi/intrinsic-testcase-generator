/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    55942, 60876, 65104, 27989, 59236, 65374, 6319, 26820, 21138, 18242, 28914, 37751, 12984, 50404, 28796, 65057
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    58722, 8429, 56491, 64390, 4191, 37599, 26873, 7257, 52006, 46677, 56380, 20049, 28689, 45300, 50422, 5343
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    bool16_t masked[] = {
    0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1 (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i16m1 (data1_v, data2_v, size_t vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    55942, 8429, 56491, 64390, 59236, 65374, 6319, 26820, 21138, 46677, 56380, 37751, 28689, 50404, 50422, 5343
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
