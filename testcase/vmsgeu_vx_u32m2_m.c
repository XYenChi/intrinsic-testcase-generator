/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    166, 78, 198, 72, 39, 225, 135, 32, 101, 198, 183, 0, 90, 247, 24, 172
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    5, 173, 128, 44, 104, 42, 185, 12, 133, 23, 10, 145, 218, 14, 62, 89
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const uint out_data[] = {
    0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0
    };
    const uint32_t *out = &out_data[0];
    uint16_t masked[] = {
    1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0
    };
    const uint16_t *mask = &masked[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2_m (mask, in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_u32m2_m (mask, in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmsgeu_vx_32m2_b16 (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m2 (bool32_t mask, uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0
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