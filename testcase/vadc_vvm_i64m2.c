/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -6, 98, -26, -11, 39, -22, -60, 117, -77, 25, 8, 37, -80, 115, 85, 95
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    15, 124, 25, 58, -113, 13, -35, 89, 12, -101, 61, -128, -30, -49, -8, -80
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    uint32_t masked[] = {
    1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0
    };
    const uint32_t *mask = &masked[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    10, 223, 0, 47, -73, -9, -94, 206, -65, -75, 70, -91, -109, 67, 77, 15
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
