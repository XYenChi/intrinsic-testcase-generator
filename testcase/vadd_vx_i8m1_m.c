/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -12, -89, 116, 112, -52, -77, 22, -11, -43, -124, -75, -67, -96, -29, 84, 8
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -37, 25, -3, 19, 110, 8, -20, 62, -76, -110, 14, 86, -34, -69, -38, 110
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m1(avl);
    const int out_data[] = {
    75, -58, -17, -67, 65, 84, -84, 21, -101, 19, 4, -26, 96, -7, -72, 85
    };
    const int8_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1_m (mask, *in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1_m (mask, *in2, vl);
    vint8m1_t data1_v = __riscv_vle8_v_i8m1_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i8m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m1 (bool8_t mask, int8_t *out, vint8m1_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    75, -58, -17, -66, 65, 85, -84, 21, -101, 20, 5, -26, 97, -6, -72, 85
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
