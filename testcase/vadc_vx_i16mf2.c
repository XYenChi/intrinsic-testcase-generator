/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    40516, 33604, 63425, 14763, 47027, 50550, 40762, 7116, 30854, 58089, 58359, 18406, 4102, 56693, 33737, 18735
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    16097, 28440, 30869, 18260, 181, 65169, 4792, 30641, 27839, 4461, 48319, 33220, 1395, 4454, 35952, 40054
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (*in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (*in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vx_i16mf2 (data1_v, data2_v, mask, vl);
        void vint16mf2_t __riscv_vse16_v_i16 (int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    56613, 62044, 94294, 33023, 47208, 115719, 45554, 37757, 58693, 62550, 106678, 51626, 5497, 61147, 69689, 58789
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
