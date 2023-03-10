/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    43, -16, 39, 107, 67, 11, -31, -119, -99, -19, -70, -25, -66, -66, -45, 17
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    81, -46, 61, 123, 93, -12, -109, -21, -38, 74, -15, 18, 54, 107, -38, -49
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int out_data[] = {
    111, 48, 11, -38, 31, -71, -118, -1, 121, 24, -9, 2, 52, 7, -126, -73
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m2 (bool32_t mask, int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    124, 48, 11, 4294967258, 160, 4294967225, 4294967156, 4294967156, 121, 24, 4294967287, 2, 52, 7, 4294967170, 4294967264
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
