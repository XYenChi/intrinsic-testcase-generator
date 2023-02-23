/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    241, 77, 167, 113, 44, 98, 86, 102, 192, 51, 58, 14, 129, 136, 6, 194
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    112, 218, 34, 0, 25, 149, 18, 140, 136, 92, 143, 28, 137, 114, 128, 142
    };
    const int32_t *in2 = &data2[0];
    const int out_data[] = {
    191, 12, 28, 246, 255, 220, 22, 63, 42, 21, 0, 48, 121, 5, 29, 215
    };
    int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint32mf2_t out_data = __riscv_vadd_vv_i32mf2_m (mask, data1, data2, vl)
        vint32mf2_t __riscv_vse32_v_i32mf2 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    191, 295, 28, 246, 255, 247, 22, 63, 328, 143, 0, 48, 266, 5, 134, 215
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
