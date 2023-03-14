/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    235, 64, 119, 136, 102, 224, 177, 5, 26, 30, 252, 101, 144, 207, 41, 183
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    230, 206, 226, 37, 33, 62, 78, 131, 28, 191, 163, 175, 116, 6, 41, 190
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const uint out_data[] = {
    1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1
    };
    const uint32_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1
    };
    const uint64_t *mask = &masked[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2_m (mask, in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_u32mf2_m (mask, in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32mf2 (bool32_t mask, uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    1, 0, 0, 173, 135, 286, 1, 136, 54, 1, 1, 0, 260, 1, 0, 373
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
