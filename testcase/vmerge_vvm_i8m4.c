/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -1, -23, -13, -66, -30, -57, -66, 61, -99, -27, -51, -60, -124, -45, -116, 109
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -123, -52, 99, 53, 68, 38, -11, -3, 27, -24, 21, -44, -31, -87, -124, 16
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    uint2_t masked[] = {
    1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0
    };
    const uint2_t *mask = &masked[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4 (in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4 (in2, vl);
    vint8m4_t out_v = __riscv_vle8_v_i8m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_i8m4 (int8_t *out, vint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -123, -52, 99, 53, -30, -57, -66, 61, 27, -27, -51, -60, -31, -45, -116, 109
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
