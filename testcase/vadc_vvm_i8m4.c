/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    105, 76, -76, -77, -78, -123, -14, -70, -103, -116, -50, -8, 18, 103, 55, -17
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    106, 113, 90, 127, -66, -71, 125, -69, -51, -31, 84, -59, 49, 15, 21, 1
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    uint2_t masked[] = {
    0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0
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
    211, 189, 15, 50, -144, -193, 111, -139, -154, -147, 35, -66, 67, 118, 76, -16
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
