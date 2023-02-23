/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    210, 21, 55, 207, 18, 230, 30, 244, 197, 200, 237, 57, 167, 23, 3, 141
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    243, 164, 201, 66, 50, 7, 172, 149, 250, 101, 118, 198, 48, 64, 128, 102
    };
    const int64_t *in2 = &data2[0];
    const int out_data[] = {
    160, 227, 124, 159, 224, 208, 157, 50, 8, 120, 76, 32, 247, 176, 239, 87
    };
    int64_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint64m8_t out_data = __riscv_vadd_vv_i64m8_m (mask, data1, data2, vl)
        vint64m8_t __riscv_vse64_v_i64m8 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    160, 227, 124, 159, 224, 237, 202, 50, 8, 120, 76, 32, 215, 176, 239, 87
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
