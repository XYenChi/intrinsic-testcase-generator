/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    254, 233, 106, 72, 42, 192, 126, 106, 163, 100, 29, 11, 16, 232, 84, 83
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    254, 115, 101, 230, 214, 155, 17, 201, 86, 155, 128, 191, 188, 247, 139, 224
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    uint16_t masked[] = {
    0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1
    };
    const uint16_t *mask = &masked[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2 (in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_u32m2 (in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vxm_u32m2 (data1_v, data2_v, masked size_t vl);
        void __riscv_vse32_v_u32m2 (uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    254, 233, 101, 72, 214, 192, 17, 201, 163, 100, 29, 11, 188, 232, 139, 224
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
