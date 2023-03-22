/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    106, -13, -109, 58, -116, 95, 73, 4, 99, 11, -53, -23, -107, 118, 108, 85
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -56, -82, -14, -21, 21, 34, 73, 98, -30, 27, -83, 63, 67, -33, 32, -121
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    uint2_t masked[] = {
    0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0
    };
    const uint2_t *mask = &masked[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4 (in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4 (in2, vl);
    vint8m4_t out_v = __riscv_vle8_v_i8m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vxm_i8m4 (data1_v, data2_v, masked size_t vl);
        void __riscv_vse8_v_i8m4 (int8_t *out, vint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    106, -82, -14, 58, 21, 95, 73, 98, 99, 11, -53, -23, -107, 118, 32, 85
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
