/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    43, 179, 210, 37, 44, 43, 165, 127, 136, 48, 38, 73, 122, 72, 137, 196
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    206, 172, 90, 99, 187, 112, 85, 18, 147, 82, 39, 10, 36, 219, 208, 180
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    uint32_t masked[] = {
    0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1
    };
    const uint32_t *mask = &masked[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1 (in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_u32m1 (in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vxm_i32m1 (data1_v, data2_v, masked, vl);
        void __riscv_vse32_v_u32m1 (uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    249, 351, 300, 137, 231, 156, 250, 146, 284, 131, 78, 84, 159, 292, 345, 377
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
