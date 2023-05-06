/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    96, -65, 107, 109, 112, 54, 31, 0, -45, -104, -51, -107, -36, -5, -75, -26
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -36, 45, -32, 12, -84, -89, -93, 70, 47, 55, 121, 27, 3, -28, -29, -5
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const int out_data[] = {
    1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1
    };
    const int16_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0
    };
    const uint8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i16m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m2 (bool16_t mask, int16_t *out, vint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    96, 1, 107, 1, 112, 54, 0, 1, 0, 55, 121, 0, 3, 65531, 0, 1
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
