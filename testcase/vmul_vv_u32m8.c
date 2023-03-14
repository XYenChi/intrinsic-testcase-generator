/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    9, 54, 246, 135, 96, 61, 183, 37, 43, 146, 180, 145, 61, 164, 143, 45
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    206, 44, 42, 168, 110, 169, 26, 157, 158, 101, 228, 182, 169, 248, 68, 182
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8 (in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_u32m8 (in2, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i32m8 (data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m8 (uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    1854, 2376, 10332, 22680, 10560, 10309, 4758, 5809, 6794, 14746, 41040, 26390, 10309, 40672, 9724, 8190
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
