/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    83, 186, 218, 65, 101, 197, 247, 118, 200, 30, 37, 49, 36, 148, 47, 152
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    80, 172, 138, 20, 108, 124, 59, 22, 71, 202, 29, 231, 77, 241, 119, 144
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
        out_v = __riscv_vrsub_vx_u32mf2 (data1_v, data2_v, vl);
        void __riscv_vse32_v_u32mf2 (uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    4294967293, 4294967282, 4294967216, 4294967251, 7, 4294967223, 4294967108, 4294967200, 4294967167, 172, 4294967288, 182, 41, 93, 72, 4294967288
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
