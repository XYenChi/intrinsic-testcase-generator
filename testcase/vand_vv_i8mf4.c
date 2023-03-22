/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -94, -88, 110, -28, -50, -29, -75, -8, -105, 59, 114, 27, 91, 108, -128, 101
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    85, -94, 70, -55, 49, -57, 47, 26, 96, 19, 48, -16, 84, 59, 72, 99
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
        void __riscv_vse8_v_i8mf4 (int8_t *out, vint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    85, 162, 70, 201, 49, 199, 47, 26, 96, 19, 48, 240, 84, 59, 72, 99
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
