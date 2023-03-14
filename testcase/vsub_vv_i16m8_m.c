/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    127, -113, 94, -17, 67, -78, 99, -125, 21, -46, 76, -114, -82, -95, 56, -102
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -103, 94, -41, 15, -59, 117, -34, 1, 77, -83, -99, -114, 19, -122, -78, -71
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const int out_data[] = {
    0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0
    };
    const int16_t *out = &out_data[0];
    uint2_t masked[] = {
    1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1
    };
    const uint2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_i16m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m8 (bool16_t mask, int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    230, 1, 1, 0, 1, 65341, 0, 65410, 0, 37, 175, 1, 1, 0, 0, 65505
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
