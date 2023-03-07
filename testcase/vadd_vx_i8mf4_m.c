/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -89, 36, -40, 68, 0, -116, 48, 54, -29, 98, 93, -108, 5, -123, -29, 103
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    103, 76, -121, 2, -1, 122, -28, 105, -78, 122, -98, 99, -55, -14, -55, -38
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    const int out_data[] = {
    -83, 50, 7, -26, -122, -46, -58, -102, -59, -66, -106, -11, 32, -71, 60, 55
    };
    const int8_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, *in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4_m (mask, *in2, vl);
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i8mf4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf4 (bool8_t mask, int8_t *out, vint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -82, 51, 8, -26, -122, -46, -57, -102, -58, -66, -106, -10, 33, -70, 61, 56
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
