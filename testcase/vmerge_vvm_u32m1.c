/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    68, 116, 71, 135, 115, 197, 175, 60, 237, 43, 167, 123, 11, 173, 30, 204
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    71, 3, 41, 169, 114, 162, 125, 128, 39, 103, 93, 94, 42, 157, 132, 48
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    uint32_t masked[] = {
    0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1
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
    68, 3, 41, 135, 114, 162, 175, 60, 237, 103, 93, 123, 42, 157, 132, 48
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
