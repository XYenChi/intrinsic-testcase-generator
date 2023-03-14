/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    79, -38, 58, -90, -16, 26, 64, 112, 96, -52, 42, 86, 82, -22, -14, -4
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    13, 95, -102, 113, 10, 86, -22, 11, 47, -53, 22, 25, -36, -70, 48, -20
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int out_data[] = {
    1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1
    };
    const int32_t *out = &out_data[0];
    uint32_t masked[] = {
    1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1
    };
    const uint32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_i32m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (bool32_t mask, int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    66, 1, 1, 4294967093, 0, 1, 0, 0, 1, 1, 20, 61, 118, 48, 1, 16
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
