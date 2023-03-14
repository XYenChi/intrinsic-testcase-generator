/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    250, 69, 240, 177, 116, 210, 222, 157, 207, 194, 136, 248, 165, 0, 206, 78
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    55, 130, 178, 238, 226, 81, 155, 117, 98, 54, 248, 144, 128, 157, 73, 47
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const uint out_data[] = {
    1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0
    };
    const uint32_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0
    };
    const uint64_t *mask = &masked[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2_m (mask, in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_u32mf2_m (mask, in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i32mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32mf2 (bool32_t mask, uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    1, 0, 42720, 42126, 0, 17010, 34410, 18369, 20286, 0, 33728, 0, 1, 0, 1, 0
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
