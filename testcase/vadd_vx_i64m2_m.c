/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -37, -127, -61, 55, 85, -112, 82, -61, 58, 37, -97, -98, 114, -102, -66, 106
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    25, -66, 99, 80, -104, 51, 92, -101, -57, 70, -94, -63, 15, -119, 118, -77
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int out_data[] = {
    75, 103, -60, 100, 81, 0, 72, 113, -69, 82, -75, -82, -126, 98, 98, -115
    };
    const int64_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2_m (mask, in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2_m (mask, in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m2 (bool64_t mask, int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    18446744073709551604, 103, 18446744073709551556, 135, 81, 18446744073709551555, 174, 113, 18446744073709551547, 107, 18446744073709551541, 18446744073709551534, 18446744073709551490, 18446744073709551395, 98, 29
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
