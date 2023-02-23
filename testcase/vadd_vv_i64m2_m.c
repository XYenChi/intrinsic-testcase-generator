/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    57, 168, 60, 197, 73, 254, 191, 9, 116, 6, 236, 80, 200, 139, 221, 66
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    13, 136, 200, 169, 172, 219, 125, 97, 36, 248, 211, 177, 6, 250, 120, 90
    };
    const int64_t *in2 = &data2[0];
    const int out_data[] = {
    55, 100, 179, 227, 31, 189, 147, 194, 95, 38, 128, 200, 64, 73, 52, 122
    };
    int64_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint64m2_t out_data = __riscv_vadd_vv_i64m2_m (mask, data1, data2, vl)
        vint64m2_t __riscv_vse64_v_i64m2 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    55, 304, 260, 366, 31, 473, 316, 106, 152, 254, 128, 257, 64, 389, 52, 122
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
