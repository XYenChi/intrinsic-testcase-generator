/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -6, -23, -56, -44, -106, -47, -89, -29, -36, 47, 85, 117, 42, -21, 4, 127
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    57, 59, -23, -44, -111, 89, 84, 15, -35, 80, -113, -127, 41, 105, 29, 76
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    const int out_data[] = {
    1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1
    };
    const int8_t *out = &out_data[0];
    uint32_t masked[] = {
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0
    };
    const uint32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4_m (mask, in2, vl);
    vint8mf4_t out_v = __riscv_vle8_v_i8mf4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_i8mf4 (bool8_t mask, int8_t *out, vint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -12, -46, -112, -44, -212, -94, -89, -58, -72, 47, 170, 234, 84, -42, 8, 127
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
