/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    195, 174, 169, 111, 134, 2, 1, 153, 119, 57, 9, 121, 121, 219, 65, 67
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    79, 74, 206, 234, 117, 37, 59, 252, 192, 244, 176, 208, 190, 57, 120, 3
    };
    const int64_t *in2 = &data2[0];
    const int out_data[] = {
    202, 188, 162, 98, 162, 9, 73, 98, 91, 79, 191, 165, 131, 140, 64, 191
    };
    int64_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint64m1_t out_data = __riscv_vadd_vv_i64m1_m (mask, data1, data2, vl)
        vint64m1_t __riscv_vse64_v_i64m1 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    274, 248, 375, 98, 251, 9, 60, 98, 91, 301, 185, 165, 311, 140, 64, 191
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
