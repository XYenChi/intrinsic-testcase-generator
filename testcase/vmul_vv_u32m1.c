/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    144, 170, 212, 149, 199, 52, 171, 245, 79, 71, 107, 41, 237, 194, 80, 67
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    161, 81, 216, 187, 103, 72, 193, 216, 63, 254, 227, 80, 70, 238, 170, 28
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1 (in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_u32m1 (in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i32m1 (data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m1 (uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    23184, 13770, 45792, 27863, 20497, 3744, 33003, 52920, 4977, 18034, 24289, 3280, 16590, 46172, 13600, 1876
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
