/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    83, 12, 1, 110, 74, 129, 34, 149, 27, 76, 12, 123, 81, 89, 157, 115
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    117, 36, 104, 55, 86, 225, 25, 34, 115, 164, 73, 73, 173, 68, 50, 214
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const uint out_data[] = {
    0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1
    };
    const uint32_t *out = &out_data[0];
    uint32_t masked[] = {
    0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1
    };
    const uint32_t *mask = &masked[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1_m (mask, in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_u32m1_m (mask, in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_u32m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m1 (bool32_t mask, uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    0, 433, 1, 6050, 0, 0, 851, 1, 1, 12464, 876, 0, 1, 1, 1, 24611
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