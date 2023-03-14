/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    76, 119, 185, 207, 209, 193, 94, 33, 90, 143, 111, 247, 105, 200, 111, 70
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    146, 17, 147, 115, 64, 117, 52, 113, 251, 49, 71, 77, 170, 117, 98, 97
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const uint out_data[] = {
    0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1
    };
    const uint32_t *out = &out_data[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8 (in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_u32m8 (in2, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m8 (uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
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
