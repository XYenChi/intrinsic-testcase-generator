/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    181, 31, 133, 80, 100, 0, 249, 147, 121, 228, 108, 248, 179, 32, 184, 151
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    186, 4, 67, 231, 203, 234, 172, 227, 101, 246, 146, 132, 184, 16, 40, 238
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const uint out_data[] = {
    1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0
    };
    const uint32_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0
    };
    const uint64_t *mask = &masked[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2_m (mask, in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_u32mf2_m (mask, in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vwmulu_vx_u32mf2_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32mf2 (bool32_t mask, uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    33666, 124, 0, 18480, 1, 0, 1, 33369, 12221, 0, 0, 32736, 1, 512, 1, 0
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
