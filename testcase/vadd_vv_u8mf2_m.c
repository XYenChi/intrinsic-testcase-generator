/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -53, -63, 54, 53, -51, -27, 107, -32, -5, 125, -39, 44, 95, 27, 106, 10
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    120, -67, 95, -34, 8, -50, 59, 62, -47, -100, 56, 64, -42, 95, 22, 9
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    const int out_data[] = {
    17, -1, -10, -82, -42, 106, -93, 54, -53, -112, -112, 22, -70, -40, -31, -22
    };
    const int8_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2_m (mask, *in2, vl);
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u8mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf2 (bool8_t mask, int8_t *out, vint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    17, -1, -10, -81, -42, 107, -93, 55, -53, -111, -112, 22, -70, -39, -31, -21
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
