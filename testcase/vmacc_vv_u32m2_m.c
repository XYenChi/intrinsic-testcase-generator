/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    101, 190, 188, 197, 163, 158, 128, 246, 183, 108, 212, 228, 233, 155, 208, 110
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    0, 42, 142, 108, 82, 27, 137, 39, 163, 204, 80, 103, 55, 200, 251, 9
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const uint out_data[] = {
    0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0
    };
    const uint32_t *out = &out_data[0];
    uint16_t masked[] = {
    1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1
    };
    const uint16_t *mask = &masked[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2_m (mask, in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_u32m2_m (mask, in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_u32m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m2 (bool32_t mask, uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    0, 0, 0, 1, 13366, 4267, 1, 9595, 1, 22032, 16961, 0, 0, 0, 0, 990
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
