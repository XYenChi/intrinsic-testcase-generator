/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -77, 17, -63, 42, 105, 75, 87, 61, 71, -46, -94, 120, 32, -102, 34, 77
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    30, 17, 25, -28, 17, 63, 47, -58, 8, 72, -50, 107, -81, -105, 34, 98
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const int out_data[] = {
    1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0
    };
    const int64_t *out = &out_data[0];
    uint16_t masked[] = {
    1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1
    };
    const uint16_t *mask = &masked[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4_m (mask, in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4_m (mask, in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vv_i64m4_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m4 (bool64_t mask, int64_t *out, vint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    2311, 18446744073709551328, 0, 0, 18446744073709549831, 0, 18446744073709547528, 3538, 0, 3312, 1, 18446744073709538777, 0, 0, 18446744073709550460, 18446744073709544070
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
