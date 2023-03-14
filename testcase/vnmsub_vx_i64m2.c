/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    61, -35, 12, -113, -128, -111, -49, -27, -94, -103, -6, -90, -124, -57, 62, -111
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -25, -94, -5, 58, 17, -2, 5, -8, -65, 50, -13, 73, -75, 0, 113, 70
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
        out_v = __riscv_vnmsub_vx_i64m2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    86, 59, 12, 18446744073709551503, 18446744073709551471, 18446744073709551507, 18446744073709551562, 18446744073709551597, 18446744073709551587, 18446744073709551463, 18446744073709551610, 18446744073709551526, 18446744073709551492, 18446744073709551559, 62, 18446744073709551505
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
