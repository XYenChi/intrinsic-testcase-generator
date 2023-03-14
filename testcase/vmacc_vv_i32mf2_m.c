/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -45, 18, 56, 41, 103, -34, -20, 114, -104, 102, -59, 120, -19, 96, 113, 64
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    14, -10, 76, 117, -97, 58, 110, 73, -86, 87, -14, -56, 25, 124, -6, 72
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int out_data[] = {
    0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0
    };
    const int32_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0
    };
    const uint64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i32mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32mf2 (bool32_t mask, int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4294966666, 4294967116, 1, 4798, 4294957305, 4294965325, 4294965096, 8323, 0, 8874, 826, 1, 1, 11905, 0, 0
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
