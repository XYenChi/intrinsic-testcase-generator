/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    39, 233, 33, 184, 45, 37, 118, 218, 15, 50, 144, 10, 204, 58, 170, 196
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    8, 109, 57, 37, 3, 150, 108, 160, 46, 43, 188, 238, 166, 164, 45, 75
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const uint out_data[] = {
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1
    };
    const uint32_t *out = &out_data[0];
    uint4_t masked[] = {
    0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1
    };
    const uint4_t *mask = &masked[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8_m (mask, in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_u32m8_m (mask, in2, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_u32m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m8 (bool32_t mask, uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    1, 25398, 1882, 6809, 1, 1, 1, 0, 690, 0, 27072, 0, 33865, 0, 7650, 14701
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
