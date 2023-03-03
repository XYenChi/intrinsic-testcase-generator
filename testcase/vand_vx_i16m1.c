/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    48986, 20349, 5478, 34947, 26033, 53867, 3816, 48843, 53669, 56900, 42512, 28197, 30532, 47642, 32785, 20974
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    20917, 25740, 25663, 23171, 24456, 13061, 38363, 55965, 42211, 34450, 18453, 7474, 56505, 38090, 12894, 10042
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1 (*in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1 (*in2, size_t vl);
    vint16m1_t out_v = __riscv_vle16_v_i16m1 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16m1_t __riscv_vse16_v_i16 (int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    20917, 25740, 25663, 23171, 24456, 13061, 38363, 55965, 42211, 34450, 18453, 7474, 56505, 38090, 12894, 10042
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
