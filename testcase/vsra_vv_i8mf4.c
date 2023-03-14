/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    49, -59, -106, 5, 39, 106, 103, 112, 47, -46, -16, 46, 57, 3, -101, 94
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -25, -40, 103, 95, 118, 100, -81, 6, 18, 60, 51, 80, -6, -49, 31, 115
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4 (in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4 (in2, vl);
    vint8mf4_t out_v = __riscv_vle8_v_i8mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsra_vv_i8mf4 (data1_v, shift, vl);
        void __riscv_vse8_v_i8mf4 (int8_t *out, vint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0
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
