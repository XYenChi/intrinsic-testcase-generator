/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -91, -16, 13, -29, 110, -78, -40, 84, 99, -98, 98, 34, -16, 114, -80, 18
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    16, 66, -119, -121, -49, -42, -82, -38, 115, -16, 121, 86, 29, -105, -110, 41
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    uint64_t masked[] = {
    1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0
    };
    const uint64_t *mask = &masked[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1 (in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m1 (int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    -74, 50, -106, -149, 62, -119, -121, 47, 215, -113, 220, 120, 14, 10, -190, 59
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
