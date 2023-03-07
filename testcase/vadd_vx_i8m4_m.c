/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -41, 74, 17, 45, -17, 59, 68, 11, -14, -127, -79, -66, 28, 82, 40, -97
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -2, 98, -100, -73, -124, -102, 68, -31, -49, 73, -78, 74, 76, -72, -64, -15
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    const int out_data[] = {
    19, 54, 85, -108, -84, 81, 116, 68, -127, 66, -60, 62, 47, -9, -99, -74
    };
    const int8_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0
    };
    const bool2_t *mask = &masked[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4_m (mask, *in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4_m (mask, *in2, vl);
    vint8m4_t data1_v = __riscv_vle8_v_i8m4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i8m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m4 (bool8_t mask, int8_t *out, vint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    20, 54, 86, -108, -83, 81, 116, 68, -126, 67, -59, 63, 47, -8, -99, -74
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
