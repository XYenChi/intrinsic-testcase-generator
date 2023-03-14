/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -126, 67, 59, 26, -126, -120, -85, -62, -33, -88, -10, -11, -2, 7, 58, -30
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -18, 2, -23, -14, -128, 120, -74, -24, 114, -109, -71, -31, -15, -3, 47, -74
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709551598, 2, 18446744073709551593, 18446744073709551602, 18446744073709551488, 120, 18446744073709551542, 18446744073709551592, 114, 18446744073709551507, 18446744073709551545, 18446744073709551585, 18446744073709551601, 18446744073709551613, 47, 18446744073709551542
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
