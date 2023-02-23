/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    22, 164, 13, 33, 103, 147, 92, 170, 244, 244, 16, 77, 69, 29, 99, 96
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    166, 95, 49, 151, 107, 140, 204, 103, 69, 175, 221, 24, 72, 78, 62, 32
    };
    const int32_t *in2 = &data2[0];
    const int out_data[] = {
    173, 122, 253, 127, 35, 118, 219, 135, 32, 255, 35, 10, 231, 120, 188, 22
    };
    int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint32m8_t out_data = __riscv_vadd_vv_i32m8_m (mask, data1, data2, vl)
        vint32m8_t __riscv_vse32_v_i32m8 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    173, 259, 253, 184, 35, 287, 296, 135, 313, 419, 35, 10, 231, 107, 188, 128
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
