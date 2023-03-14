/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    28, 80, -12, 126, 118, -15, 81, 107, 64, -115, -91, -114, 106, -2, -69, 83
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -48, 120, -104, 44, 114, -27, -33, 69, 5, -79, -122, -41, 57, 109, -46, -110
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int out_data[] = {
    0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0
    };
    const int64_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1
    };
    const uint64_t *mask = &masked[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1_m (mask, in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1_m (mask, in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vv_i64m1_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m1 (bool64_t mask, int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    0, 18446744073709551576, 0, 1, 118, 12, 114, 38, 59, 18446744073709551580, 18446744073709551525, 18446744073709551543, 49, 0, 18446744073709551593, 83
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
