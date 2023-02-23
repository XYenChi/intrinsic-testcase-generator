/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    212, 86, 37, 18, 8, 200, 169, 84, 227, 220, 159, 32, 224, 158, 97, 194
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    156, 168, 211, 222, 175, 114, 240, 112, 193, 109, 208, 38, 196, 208, 120, 94
    };
    const int64_t *in2 = &data2[0];
    const int out_data[] = {
    220, 200, 81, 39, 131, 88, 182, 122, 230, 99, 40, 206, 90, 139, 1, 61
    };
    int64_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint64m4_t out_data = __riscv_vadd_vv_i64m4_m (mask, data1, data2, vl)
        vint64m4_t __riscv_vse64_v_i64m4 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    368, 254, 81, 240, 183, 88, 182, 196, 420, 99, 367, 206, 90, 366, 1, 61
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
