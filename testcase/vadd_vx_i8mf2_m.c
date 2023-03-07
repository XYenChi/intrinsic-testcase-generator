/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -30, -127, 17, -8, -75, 57, -124, 74, 60, -7, -36, 54, 8, 101, 43, 121
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    48, -42, 30, -60, 115, 72, -78, -26, 38, 8, 34, -119, -126, -33, 76, -20
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    const int out_data[] = {
    -93, 24, -28, -56, 116, 116, -33, 14, -20, -67, -50, -28, 46, 32, -36, -124
    };
    const int8_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2_m (mask, *in2, vl);
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i8mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf2 (bool8_t mask, int8_t *out, vint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -93, 24, -27, -55, 117, 117, -32, 14, -20, -67, -49, -28, 46, 32, -36, -123
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
