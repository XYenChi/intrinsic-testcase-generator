/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    197, 201, 43, 248, 138, 232, 101, 161, 210, 29, 157, 8, 145, 215, 82, 181
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    241, 242, 80, 182, 57, 234, 208, 156, 148, 216, 160, 200, 224, 159, 98, 22
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2 (in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_u32m2 (in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_u32m2 (data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m2 (uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    47477, 48642, 3440, 45136, 7866, 54289, 21009, 25117, 31081, 6264, 25121, 1601, 32480, 34186, 8036, 3983
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
