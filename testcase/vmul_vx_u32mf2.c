/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    185, 146, 151, 73, 7, 186, 36, 32, 245, 28, 41, 52, 167, 165, 155, 128
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    72, 6, 242, 64, 202, 211, 22, 220, 108, 129, 204, 56, 192, 166, 34, 214
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
        out_v = __riscv_vmul_vx_i32mf2 (data1_v, data2_v, vl);
        void __riscv_vse32_v_u32mf2 (uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    13320, 876, 36542, 4672, 1414, 39246, 792, 7040, 26460, 3612, 8364, 2912, 32064, 27390, 5270, 27392
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
