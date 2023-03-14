/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    96, 17, -14, -32, 89, 35, -27, 63, 60, -8, 69, -7, -100, -50, -29, 38
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    39, 83, 87, -44, -34, 80, -8, -95, -15, 66, -98, -44, -74, 43, -84, -43
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
        void __riscv_vse64_v_i64m1 (int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    39, 83, 87, 18446744073709551572, 18446744073709551582, 80, 18446744073709551608, 18446744073709551521, 18446744073709551601, 66, 18446744073709551518, 18446744073709551572, 18446744073709551542, 43, 18446744073709551532, 18446744073709551573
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
