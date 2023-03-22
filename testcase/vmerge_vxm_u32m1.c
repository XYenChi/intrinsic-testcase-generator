/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    171, 0, 203, 13, 42, 212, 33, 172, 143, 18, 224, 29, 162, 247, 158, 110
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    143, 162, 14, 18, 255, 219, 137, 179, 31, 227, 16, 79, 67, 10, 132, 18
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    uint32_t masked[] = {
    1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1
    };
    const uint32_t *mask = &masked[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1 (in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_u32m1 (in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vxm_u32m1 (data1_v, data2_v, masked size_t vl);
        void __riscv_vse32_v_u32m1 (uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    143, 0, 14, 13, 42, 219, 137, 172, 143, 18, 16, 79, 67, 10, 132, 18
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
