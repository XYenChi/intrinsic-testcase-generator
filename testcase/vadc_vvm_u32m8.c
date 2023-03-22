/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    1, 8, 181, 83, 182, 239, 36, 99, 111, 236, 93, 56, 219, 56, 43, 190
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    34, 214, 52, 96, 19, 86, 223, 232, 53, 59, 30, 174, 210, 224, 104, 175
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    uint4_t masked[] = {
    0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0
    };
    const uint4_t *mask = &masked[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8 (in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_u32m8 (in2, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vvm_i32m8 (data1_v, data2_v, masked, vl);
        void __riscv_vse32_v_u32m8 (uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    35, 223, 234, 180, 202, 325, 260, 331, 164, 295, 123, 231, 430, 280, 147, 365
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
