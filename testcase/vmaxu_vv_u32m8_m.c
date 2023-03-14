/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    197, 112, 253, 8, 77, 189, 92, 88, 134, 168, 83, 44, 194, 109, 136, 101
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    246, 92, 183, 207, 22, 3, 182, 99, 217, 52, 34, 51, 136, 189, 235, 240
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const uint out_data[] = {
    1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0
    };
    const uint32_t *out = &out_data[0];
    uint4_t masked[] = {
    1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1
    };
    const uint4_t *mask = &masked[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8_m (mask, in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_u32m8_m (mask, in2, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m8 (bool32_t mask, uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    246, 1, 0, 0, 77, 0, 1, 1, 1, 1, 83, 1, 1, 189, 235, 240
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
