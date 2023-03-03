/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    61312, 34946, 56012, 12135, 46142, 55294, 32576, 35370, 24539, 24445, 25133, 30665, 53974, 56154, 29861, 16887
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    8840, 31216, 21450, 16061, 53988, 39384, 63292, 34823, 45014, 44134, 2225, 29465, 54544, 21783, 586, 61518
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (*in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (*in2, size_t vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16mf4_t __riscv_vse16_v_i16 (int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    8840, 31216, 21450, 16061, 53988, 39384, 63292, 34823, 45014, 44134, 2225, 29465, 54544, 21783, 586, 61518
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
