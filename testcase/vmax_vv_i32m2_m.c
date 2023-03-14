/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -91, -127, 40, -14, -110, -48, 93, -89, 29, 6, 76, 13, -25, -19, -20, 0
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    67, -76, -71, 122, 66, 4, 15, 123, -15, -46, 35, 39, -103, 51, 18, 46
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int out_data[] = {
    0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0
    };
    const int32_t *out = &out_data[0];
    uint16_t masked[] = {
    0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0
    };
    const uint16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i32m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m2 (bool32_t mask, int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    0, 1, 40, 1, 0, 4, 93, 0, 0, 6, 1, 39, 1, 0, 18, 0
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
