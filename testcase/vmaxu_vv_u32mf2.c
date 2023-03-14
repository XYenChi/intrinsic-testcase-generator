/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    108, 5, 94, 233, 123, 161, 140, 189, 148, 21, 15, 168, 8, 169, 82, 236
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    66, 137, 186, 21, 194, 47, 182, 197, 232, 107, 152, 69, 101, 172, 244, 63
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2 (in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_u32mf2 (in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32mf2 (uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    108, 137, 186, 233, 194, 161, 182, 197, 232, 107, 152, 168, 101, 172, 244, 236
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
