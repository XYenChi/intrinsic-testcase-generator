/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    26459, 31641, 6110, 63260, 27081, 39317, 53841, 58927, 34763, 55947, 19573, 10557, 61936, 53856, 9662, 44886
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    23348, 16804, 5936, 23933, 43116, 14144, 3198, 34883, 64647, 14049, 20808, 60873, 2777, 54380, 59628, 2590
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    4857, 39812, 55549, 48959, 28515, 83, 45582, 35559, 15297, 30495, 53242, 11863, 894, 43901, 200, 55523
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    4857, 39812, 12046, 48959, 70197, 53461, 45582, 93810, 15297, 30495, 53242, 11863, 64713, 43901, 200, 55523
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
