/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    156, 34, 159, 170, 201, 141, 92, 145, 24, 66, 196, 160, 216, 15, 189, 220
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    74, 206, 38, 32, 194, 150, 56, 213, 194, 92, 220, 225, 41, 3, 83, 210
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const uint out_data[] = {
    1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0
    };
    const uint32_t *out = &out_data[0];
    uint32_t masked[] = {
    1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1
    };
    const uint32_t *mask = &masked[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1_m (mask, in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_u32m1_m (mask, in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m1 (bool32_t mask, uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    74, 0, 38, 32, 1, 150, 1, 213, 0, 1, 220, 225, 41, 0, 83, 210
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
