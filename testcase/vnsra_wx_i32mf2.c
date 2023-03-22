/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    76, -49, -121, 67, 93, -106, -83, 0, 61, 70, -121, 57, 33, -124, 72, 102
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -19, -24, 19, 23, 43, -24, 7, 18, -80, -63, 113, -38, 38, -6, -57, -113
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnsra_wx_32mf2 (data1_v, shift, vl);
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
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
