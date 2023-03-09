/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -18, -95, -21, -83, 118, -27, 28, 115, 62, -45, -71, 127, 21, -63, -63, 96
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -128, -80, -16, -37, 71, 12, -50, -40, -38, -90, -36, -52, 38, 8, -127, 85
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const int out_data[] = {
    -46, 116, -18, -109, 94, -6, 103, 62, -15, -71, 114, 41, 88, 14, -120, -48
    };
    const int64_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0
    };
    const bool16_t *mask = &masked[0];
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
    18446744073709551470, 116, 18446744073709551579, 18446744073709551496, 94, 18446744073709551601, 18446744073709551594, 62, 24, 18446744073709551481, 114, 41, 59, 18446744073709551561, 18446744073709551426, 18446744073709551568
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
