/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    54, 90, -20, -113, 124, -84, 36, 28, 91, -98, -111, -14, -89, -70, 38, -7
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -54, -18, 11, -3, 38, -104, -67, -61, -60, 10, 66, -28, 126, 11, 99, -100
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (in1, vl);
    vuint64m2_t data2_v = __riscv_vle64_v_i64m2 (in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vwmul_vx_i64m2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709548700, 18446744073709549996, 18446744073709551396, 339, 4712, 8736, 18446744073709549204, 18446744073709549908, 18446744073709546156, 18446744073709550636, 18446744073709544290, 392, 18446744073709540402, 18446744073709550846, 3762, 700
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
