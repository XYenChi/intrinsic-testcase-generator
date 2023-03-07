/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    17480, -29138, -4789, 7063, -16244, 28824, 24102, -28496, -28364, -20053, 7243, -24390, 2048, 1538, 934, 619
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -3693, 17827, 23431, -16319, 26092, -10743, 11525, 5286, 10100, -16050, -13195, -1053, -15181, 1094, -11379, -25643
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const int out_data[] = {
    12770, 10149, 7305, 21113, 15172, -6852, 32042, -22190, 10436, 25674, 20409, 23737, 24445, -22231, 3626, 21802
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u16mf4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf4 (bool16_t mask, int16_t *out, vint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    12771, 10149, 7305, 21113, 15173, -6851, 32043, -22190, 10437, 25675, 20409, 23738, 24446, -22230, 3626, 21803
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
