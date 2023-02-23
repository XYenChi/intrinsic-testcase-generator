/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    74, 148, 74, 238, 63, 25, 252, 148, 4, 165, 204, 50, 221, 20, 34, 48
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    69, 201, 8, 20, 74, 212, 55, 69, 65, 136, 124, 128, 208, 196, 240, 8
    };
    const int64_t *in2 = &data2[0];
    const int out_data[] = {
    103, 195, 153, 204, 54, 166, 38, 195, 229, 252, 109, 56, 24, 4, 0, 221
    };
    int64_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint64m2_t out_data = __riscv_vadd_vx_i64m2_m (mask, data1, data2, vl)
        vint64m2_t __riscv_vse64_v_i64m2 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    103, 195, 82, 258, 137, 166, 307, 195, 229, 301, 328, 56, 24, 216, 0, 56
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
