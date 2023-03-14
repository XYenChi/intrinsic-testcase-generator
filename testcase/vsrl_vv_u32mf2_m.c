/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    182, 85, 70, 30, 3, 24, 135, 125, 129, 68, 55, 56, 158, 196, 56, 219
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    238, 198, 254, 223, 235, 184, 185, 25, 56, 26, 106, 19, 51, 186, 189, 249
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const uint out_data[] = {
    0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0
    };
    const uint32_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0
    };
    const uint64_t *mask = &masked[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2_m (mask, in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_u32mf2_m (mask, in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsrl_vv_u32mf2_m (mask, data1_v, shift, vl);
        void __riscv_vse32_v_u32mf2 (bool32_t mask, uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    182, 85, 70, 15, 1, 24, 67, 62, 129, 68, 55, 28, 79, 196, 28, 109
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
