/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    67, -88, -51, -117, -38, -43, -111, 34, 93, -104, 49, 114, 29, 18, 94, -10
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -2, 114, 114, 1, -83, 102, 90, -38, -106, -79, -9, -6, -16, 64, 112, -46
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8 (in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8 (in2, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vx_i64m8 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m8 (int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    69, 18446744073709551528, 18446744073709551451, 18446744073709551499, 18446744073709551578, 18446744073709551471, 18446744073709551415, 72, 199, 18446744073709551512, 49, 120, 29, 18446744073709551570, 18446744073709551598, 18446744073709551606
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
