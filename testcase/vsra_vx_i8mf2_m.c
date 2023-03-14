/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    107, -57, 46, 86, -81, 127, 93, 13, -54, -86, -67, 73, -108, -76, -21, -98
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -100, 73, -22, 44, 105, 48, 75, 74, -81, -97, 38, -101, -76, -105, -4, 85
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    const int out_data[] = {
    0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0
    };
    const int8_t *out = &out_data[0];
    uint16_t masked[] = {
    1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1
    };
    const uint16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2_m (mask, in2, vl);
    vint8mf2_t out_v = __riscv_vle8_v_i8mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsra_vx_i8mf2_m (mask, data1_v, shift, vl);
        void __riscv_vse8_v_i8mf2 (bool8_t mask, int8_t *out, vint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    107, -29, 46, 86, -41, 127, 46, 13, -27, -43, -67, 36, -108, -38, -21, -49
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
