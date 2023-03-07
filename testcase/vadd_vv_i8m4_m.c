/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    60, 38, 35, -54, -96, 54, 18, -49, -10, -33, -50, -56, 1, 36, -82, 52
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    100, -31, 1, -62, -80, -89, 93, -120, -98, 79, -28, -54, -21, -85, 81, 72
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    const int out_data[] = {
    61, 55, -48, 125, 50, 47, 1, 89, 2, 116, -4, 99, -15, 83, -22, -42
    };
    const int8_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1
    };
    const bool2_t *mask = &masked[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4_m (mask, *in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4_m (mask, *in2, vl);
    vint8m4_t data1_v = __riscv_vle8_v_i8m4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i8m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m4 (bool8_t mask, int8_t *out, vint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    62, 55, -48, 126, 51, 47, 1, 89, 2, 117, -4, 100, -14, 84, -22, -41
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
