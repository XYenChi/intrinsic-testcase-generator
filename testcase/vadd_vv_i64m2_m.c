/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -107, 99, 111, -95, -36, 57, 73, 49, 64, -70, 91, 20, -72, -52, 40, -37
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    96, 122, -16, -21, -64, -74, 19, -62, 115, 76, -46, -107, 109, -118, -49, 74
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int out_data[] = {
    -80, -17, 80, -2, -8, -16, -121, 78, 34, -96, 74, 77, 3, 9, 32, -128
    };
    const int64_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1
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
    18446744073709551536, 221, 80, 18446744073709551614, 18446744073709551608, 18446744073709551600, 92, 78, 179, 6, 45, 18446744073709551529, 37, 18446744073709551446, 32, 37
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
