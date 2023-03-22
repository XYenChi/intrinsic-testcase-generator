/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    31, -16, 24, 76, -123, 13, 108, -83, 41, 22, -18, 127, -55, -105, 60, 69
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    80, 75, 110, -58, -65, -124, -76, -42, -27, -45, 85, 70, 71, -45, -114, 21
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8 (in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8 (in2, vl);
    vint8mf8_t out_v = __riscv_vle8_v_i8mf8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i8mf8 (data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf8 (int8_t *out, vint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    80, 75, 110, 76, 191, 13, 108, 214, 41, 22, 85, 127, 71, 211, 60, 69
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
