/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -88, 65, -4, 24, 63, -50, 82, -73, 71, -45, -115, -80, -21, 83, 46, 92
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    66, 12, 10, 0, -78, -124, 48, 58, 2, -88, 111, 67, -63, 19, -78, 68
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const int out_data[] = {
    -7, 83, 31, -51, 15, -124, -79, -125, 11, -26, 44, -14, 40, 127, -80, 96
    };
    const int64_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8_m (mask, in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8_m (mask, in2, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m8 (bool64_t mask, int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    18446744073709551594, 83, 31, 24, 15, 18446744073709551492, 130, 18446744073709551491, 73, 18446744073709551590, 44, 18446744073709551603, 40, 127, 18446744073709551584, 96
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
