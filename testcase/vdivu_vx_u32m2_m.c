/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    203, 13, 155, 36, 112, 149, 16, 85, 108, 17, 52, 44, 180, 212, 16, 72
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    249, 9, 33, 136, 135, 116, 144, 128, 225, 173, 82, 113, 36, 171, 161, 108
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const uint out_data[] = {
    0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1
    };
    const uint32_t *out = &out_data[0];
    uint16_t masked[] = {
    1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0
    };
    const uint16_t *mask = &masked[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2_m (mask, in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_u32m2_m (mask, in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdivu_vx_i32m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m2 (bool32_t mask, uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    1, 0, 0, 3, 1, 0, 9, 1, 1, 0, 1, 2, 0, 0, 10, 1
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
