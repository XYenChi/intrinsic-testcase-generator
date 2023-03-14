/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    191, 160, 105, 34, 152, 26, 230, 34, 161, 226, 90, 137, 220, 183, 171, 55
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    198, 180, 118, 179, 94, 253, 178, 6, 245, 118, 185, 168, 114, 240, 98, 230
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    uint32_t masked[] = {
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0
    };
    const uint32_t *mask = &masked[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1 (in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_u32m1 (in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m1 (uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    191, 160, 105, 34, 152, 253, 178, 6, 161, 226, 185, 137, 220, 240, 171, 55
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
