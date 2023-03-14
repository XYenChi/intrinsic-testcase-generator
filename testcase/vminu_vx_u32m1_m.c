/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    198, 2, 226, 7, 179, 232, 105, 14, 190, 134, 42, 116, 122, 154, 28, 184
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    151, 118, 158, 194, 4, 105, 57, 237, 130, 226, 53, 81, 140, 182, 167, 196
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const uint out_data[] = {
    1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0
    };
    const uint32_t *out = &out_data[0];
    uint32_t masked[] = {
    0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1
    };
    const uint32_t *mask = &masked[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1_m (mask, in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_u32m1_m (mask, in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m1 (bool32_t mask, uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    1, 0, 0, 0, 0, 232, 105, 0, 1, 0, 53, 0, 140, 1, 167, 196
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
