/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -5045, -8311, 1502, -35, -29506, 25690, 6386, 23604, 7238, -26256, -11008, -7551, -1514, -26087, -29199, 11738
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    19961, -14981, -16204, 4095, -12647, -18803, -21757, 30780, 30594, 4999, 25017, -16995, 21467, 23935, -32644, 21061
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const int out_data[] = {
    -22025, 21794, 29723, 28638, -7302, -813, -14236, 32146, -26147, 21209, 16900, 10300, -5289, 22832, 3014, 19145
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u16m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m1 (bool16_t mask, int16_t *out, vint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -22024, 21794, 29724, 28638, -7302, -813, -14235, 32147, -26146, 21210, 16901, 10301, -5288, 22832, 3014, 19145
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
