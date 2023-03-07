/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -68, 121, -20, -104, 43, -26, -53, 78, -103, -123, 61, -80, 95, 71, 39, -106
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    79, 69, -95, -126, 64, -6, 40, -100, 68, -120, 106, 103, -9, 111, 25, -9
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m2(avl);
    const int out_data[] = {
    -12, 120, -111, -66, -33, 33, 34, -90, 97, -12, 67, -31, 88, -16, -124, -126
    };
    const int8_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, *in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2_m (mask, *in2, vl);
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u8m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m2 (bool8_t mask, int8_t *out, vint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -11, 120, -111, -65, -33, 33, 35, -89, 98, -11, 68, -30, 88, -16, -124, -126
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
