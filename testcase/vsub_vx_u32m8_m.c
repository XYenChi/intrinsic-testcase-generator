/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    228, 18, 248, 65, 153, 214, 130, 145, 45, 127, 203, 243, 70, 134, 232, 5
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    91, 8, 197, 224, 45, 244, 190, 24, 246, 72, 130, 226, 25, 6, 243, 185
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const uint out_data[] = {
    0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1
    };
    const uint32_t *out = &out_data[0];
    uint4_t masked[] = {
    0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0
    };
    const uint4_t *mask = &masked[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8_m (mask, in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_u32m8_m (mask, in2, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u32m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m8 (bool32_t mask, uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    0, 10, 51, 1, 0, 1, 4294967236, 121, 0, 0, 1, 0, 45, 128, 1, 1
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
