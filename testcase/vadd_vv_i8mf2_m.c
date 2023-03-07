/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    92, -28, -111, -106, 108, 103, -48, -35, 107, -117, 52, 111, -50, 57, -39, -8
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -60, 1, -23, 126, 66, 95, 0, -114, 74, 113, 108, -51, 55, -39, 122, -44
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    const int out_data[] = {
    89, 70, 67, -33, -82, -53, -122, 59, -107, -31, -127, -128, -82, 21, 32, -101
    };
    const int8_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2_m (mask, *in2, vl);
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i8mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf2 (bool8_t mask, int8_t *out, vint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    90, 70, 68, -33, -82, -53, -48, 60, -107, -30, -126, -127, -82, 21, 32, -101
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
