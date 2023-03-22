/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    166, 156, 20, 132, 121, 214, 172, 38, 116, 131, 240, 180, 213, 36, 159, 21
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    245, 235, 204, 111, 102, 22, 54, 190, 195, 231, 45, 45, 249, 32, 55, 164
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
        out_v = __riscv_vadd_vx_u32m8 (data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m8 (uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    411, 391, 224, 243, 223, 236, 226, 228, 311, 362, 285, 225, 462, 68, 214, 185
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
