/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -50, 43, 102, -124, -39, -48, 86, 84, 51, 15, 12, 114, -73, 44, -120, 101
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -77, -96, 46, -13, 90, 88, 6, 66, -71, -80, 75, -49, 70, -25, -6, -11
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const int out_data[] = {
    0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1
    };
    const int16_t *out = &out_data[0];
    uint2_t masked[] = {
    1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1
    };
    const uint2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_i16m8 (bool16_t mask, int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    65409, 65483, 148, 1, 51, 1, 1, 150, 65516, 65471, 0, 1, 65533, 19, 1, 90
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
