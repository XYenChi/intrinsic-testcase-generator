/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -5000, 19264, 3229, 32220, 9672, 21935, -496, 32259, -12299, 2268, -734, -12432, 9507, 19690, 20715, 15888
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    19199, 7259, -25894, -13243, -29616, 2707, -26192, -1648, -21601, -22475, 11308, 18887, 929, -7477, 20122, -28628
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const int out_data[] = {
    255, -13792, 28390, 891, 2322, -2337, -20991, -10367, 12626, 3945, 4640, -27763, 17176, -24122, 2054, 12692
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m2 (bool16_t mask, int16_t *out, vint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    255, -13792, 28390, 892, 2322, -2337, -20991, -10366, 12626, 3946, 4641, -27762, 17176, -24121, 2055, 12693
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
