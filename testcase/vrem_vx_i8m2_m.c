/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -126, -82, -81, 109, 124, 124, -21, -65, -69, 26, -126, -128, -89, -128, 38, 54
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -68, -101, 55, 59, -128, -49, 100, 86, 55, 67, -5, -45, -47, -37, 75, -7
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m2(avl);
    const int out_data[] = {
    1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0
    };
    const int8_t *out = &out_data[0];
    uint4_t masked[] = {
    0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0
    };
    const uint4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2_m (mask, in2, vl);
    vint8m2_t out_v = __riscv_vle8_v_i8m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i8m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m2 (bool8_t mask, int8_t *out, vint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    1, 0, 230, 59, 0, 0, 0, 1, 0, 15, 251, 1, 209, 219, 0, 0
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
