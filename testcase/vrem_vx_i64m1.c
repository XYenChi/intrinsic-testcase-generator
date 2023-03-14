/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -116, -44, 99, -64, 92, -98, 119, 94, 76, -84, -1, 38, -44, 27, -124, -53
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    96, 30, 90, -120, -24, -69, -27, 78, 8, -26, -56, -75, 88, -21, 59, 93
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
        out_v = __riscv_vrem_vx_i64m1 (data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m1 (int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709551596, 18446744073709551602, 90, 18446744073709551560, 68, 18446744073709551547, 92, 78, 8, 18446744073709551590, 0, 1, 0, 6, 18446744073709551551, 18446744073709551603
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
