/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -36, 39, -71, 13, -86, 11, 7, -4, 25, -67, -36, -26, -89, 29, 83, 94
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    113, -2, -29, -46, -113, -101, 15, 46, 11, -26, -25, 57, 89, 27, 123, 74
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m2(avl);
    uint4_t masked[] = {
    0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0
    };
    const uint4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2 (in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2 (in2, vl);
    vint8m2_t out_v = __riscv_vle8_v_i8m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vvm_i8m2 (data1_v, data2_v, masked size_t vl);
        void __riscv_vse8_v_i8m2 (int8_t *out, vint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -36, -2, -29, 13, -86, 11, 15, -4, 11, -67, -36, -26, -89, 29, 83, 94
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
