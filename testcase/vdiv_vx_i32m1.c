/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    124, -52, -124, 99, -50, 22, -34, 52, 103, 96, -6, -9, -79, 45, -70, 52
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    127, -19, 26, -2, -124, -36, -104, -80, -54, 15, -54, 32, 37, 85, 102, 3
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i32m1 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1, 0, 4294967295, 4294967295, 2, 4294967294, 3, 4294967294, 4294967295, 0, 9, 4294967292, 4294967295, 1, 4294967294, 0
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
