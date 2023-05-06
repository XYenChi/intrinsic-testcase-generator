/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    130, 124, 150, 33, 48, 90, 211, 250, 48, 4, 12, 198, 12, 195, 29, 36
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    160, 56, 63, 37, 5, 143, 113, 9, 89, 129, 223, 110, 65, 238, 183, 89
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    uint4_t masked[] = {
    0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0
    };
    const uint4_t *mask = &masked[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8 (in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_u32m8 (in2, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vxm_u32m8 (data1_v, data2_v, masked size_t vl);
        void __riscv_vse32_v_u32m8 (uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    130, 124, 63, 33, 5, 90, 113, 250, 48, 4, 223, 110, 12, 238, 183, 36
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
