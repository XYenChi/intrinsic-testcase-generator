/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    0, 60, 134, 128, 21, 77, 55, 251, 231, 67, 119, 54, 29, 178, 191, 115
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    73, 73, 38, 16, 94, 253, 208, 58, 99, 51, 86, 7, 61, 120, 56, 81
    };
    const int32_t *in2 = &data2[0];
    const int out_data[] = {
    196, 240, 230, 114, 176, 50, 211, 35, 77, 71, 52, 211, 150, 149, 148, 118
    };
    int32_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint32m2_t out_data = __riscv_vadd_vv_i32m2_m (mask, data1, data2, vl)
        vint32m2_t __riscv_vse32_v_i32m2 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    73, 240, 230, 144, 115, 330, 211, 35, 77, 118, 205, 61, 90, 298, 148, 118
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
