/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    10559, 18906, 58380, 63089, 28319, 32045, 8704, 8253, 4425, 15071, 7860, 1776, 42329, 55569, 28088, 24037
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    31311, 23557, 12510, 27303, 16805, 18165, 6429, 46817, 62201, 2810, 52332, 16687, 82, 28657, 52806, 64990
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    42174, 65457, 27063, 11604, 62651, 42216, 43041, 20719, 56169, 60417, 43020, 17616, 43468, 57964, 34347, 8837
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    445315266, 1237530043, 1579937941, 732084756, 1774213670, 1352811721, 374628864, 170993908, 248547826, 910544607, 338137201, 31286017, 1839956972, 3221001517, 964738536, 212414969
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
