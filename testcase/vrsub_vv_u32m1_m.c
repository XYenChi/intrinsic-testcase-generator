/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    40, 65, 207, 213, 131, 136, 107, 163, 117, 191, 248, 34, 112, 172, 27, 195
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    38, 68, 232, 221, 37, 89, 125, 83, 127, 189, 30, 225, 154, 41, 107, 153
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const uint out_data[] = {
    0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1
    };
    const uint32_t *out = &out_data[0];
    uint32_t masked[] = {
    0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0
    };
    const uint32_t *mask = &masked[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1_m (mask, in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_u32m1_m (mask, in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrsub_vx_u32m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m1 (bool32_t mask, uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    0, 0, 25, 8, 4294967202, 1, 18, 1, 1, 4294967294, 1, 0, 42, 4294967165, 80, 1
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
