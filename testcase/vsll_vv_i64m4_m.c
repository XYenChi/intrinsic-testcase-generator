/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    53, 125, 116, -77, 11, 58, 87, 46, 48, -5, 59, -41, 89, -41, 119, -36
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -57, 87, -47, -28, 115, -73, -67, 104, -110, 1, 46, 69, 118, 36, 34, 95
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const int out_data[] = {
    0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1
    };
    const int64_t *out = &out_data[0];
    uint16_t masked[] = {
    0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1
    };
    const uint16_t *mask = &masked[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4_m (mask, in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4_m (mask, in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m4 (bool64_t mask, int64_t *out, vint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    106, 250, 232, -77, 22, 116, 174, 46, 48, -10, 59, -82, 89, -41, 119, -72
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
