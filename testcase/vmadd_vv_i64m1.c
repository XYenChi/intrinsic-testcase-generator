/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    84, 0, 96, 9, 18, 104, -43, -31, 88, -9, 56, 74, -72, -36, 122, -74
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    86, -59, 38, 72, -88, 22, 16, -82, -31, -93, -79, 44, 61, 72, 113, -21
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1 (in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmadd_vv_i64m1 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m1 (int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    86, 18446744073709551557, 38, 81, 18446744073709551546, 126, 18446744073709551589, 18446744073709551534, 57, 18446744073709551523, 18446744073709551593, 118, 61, 36, 113, 18446744073709551521
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
