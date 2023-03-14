/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -111, 19, -78, -98, 32, 70, 5, 102, -60, 123, -118, -97, -70, 58, -30, -124
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    102, 35, 122, -4, 87, 27, 108, 69, -127, -16, 25, -69, -34, 63, 59, -101
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    const int out_data[] = {
    1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1
    };
    const int8_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1
    };
    const uint64_t *mask = &masked[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8_m (mask, in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8_m (mask, in2, vl);
    vint8mf8_t out_v = __riscv_vle8_v_i8mf8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i8mf8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf8 (bool8_t mask, int8_t *out, vint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    1, 1, 1, 0, 0, 27, 3, 69, 249, 1, 1, 1, 222, 5, 1, 155
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
