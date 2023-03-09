/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    73, -31, -34, -18, -21, -103, 45, -86, 71, 123, -98, 110, 18, 18, 62, -63
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -96, 103, 77, 104, -67, -123, -1, -60, -15, 42, -4, 106, 1, -29, 91, 23
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int out_data[] = {
    -4, -72, 2, 32, -70, 60, 111, 29, -120, 37, 28, -33, -80, -114, 4, -75
    };
    const int64_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1_m (mask, in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1_m (mask, in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m1 (bool64_t mask, int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    18446744073709551593, 18446744073709551544, 43, 86, 18446744073709551546, 18446744073709551390, 44, 18446744073709551470, 18446744073709551496, 165, 28, 216, 18446744073709551536, 18446744073709551605, 153, 18446744073709551576
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
