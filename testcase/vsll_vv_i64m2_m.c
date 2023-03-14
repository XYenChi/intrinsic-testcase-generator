/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -10, -81, -19, -105, -106, 2, -51, 95, 24, 12, -27, -82, 127, 93, -73, 32
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    43, 78, 113, 25, 127, -75, 70, 43, 6, 25, -46, -16, -69, 84, 9, -72
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int out_data[] = {
    0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0
    };
    const int64_t *out = &out_data[0];
    uint32_t masked[] = {
    1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1
    };
    const uint32_t *mask = &masked[0];
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
    -20, -81, -38, -210, -212, 4, -51, 190, 24, 24, -27, -82, 254, 93, -146, 32
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
