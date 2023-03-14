/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    77, 111, 200, 37, 233, 147, 109, 167, 166, 185, 170, 211, 219, 44, 61, 105
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    6, 243, 220, 129, 56, 68, 113, 247, 185, 83, 46, 215, 127, 1, 63, 16
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const uint out_data[] = {
    1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1
    };
    const uint32_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1
    };
    const uint64_t *mask = &masked[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2_m (mask, in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_u32mf2_m (mask, in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmadd_vx_u32mf2_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32mf2 (bool32_t mask, uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    77, 111, 200, 37, 289, 215, 113, 414, 351, 83, 216, 426, 127, 45, 61, 121
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
