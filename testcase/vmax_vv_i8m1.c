/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    67, 84, -36, -38, -104, -108, -94, -10, -50, 7, -52, 6, -84, -27, 0, 99
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    89, -16, -67, -62, -85, -31, -84, 34, 124, 45, 64, 39, -3, 73, 65, 79
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m1(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1 (in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1 (in2, vl);
    vint8m1_t out_v = __riscv_vle8_v_i8m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i8m1 (data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m1 (int8_t *out, vint8m1_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    89, 84, 220, 218, 171, 225, 172, 34, 124, 45, 64, 39, 253, 73, 65, 99
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
