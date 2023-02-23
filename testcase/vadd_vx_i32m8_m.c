/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    154, 214, 205, 199, 83, 152, 6, 107, 234, 115, 240, 48, 183, 50, 31, 202
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    149, 72, 195, 3, 29, 190, 17, 81, 234, 228, 154, 54, 133, 2, 191, 114
    };
    const int32_t *in2 = &data2[0];
    const int out_data[] = {
    218, 220, 199, 72, 196, 6, 124, 220, 27, 141, 36, 54, 208, 151, 207, 70
    };
    int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint32m8_t out_data = __riscv_vadd_vx_i32m8_m (mask, data1, data2, vl)
        vint32m8_t __riscv_vse32_v_i32m8 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    303, 220, 400, 72, 112, 6, 124, 220, 27, 141, 394, 102, 316, 52, 222, 316
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
