/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    47, -71, 34, 103, -122, 119, 54, 103, -88, 118, -52, -4, 83, -44, -80, 12
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -21, -26, -66, 116, 25, -34, 86, -60, -12, 98, -94, 76, 43, -64, -55, -73
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
        void __riscv_vse64_v_i64m8 (int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709551595, 18446744073709551590, 18446744073709551550, 116, 25, 18446744073709551582, 86, 18446744073709551556, 18446744073709551604, 98, 18446744073709551522, 76, 43, 18446744073709551552, 18446744073709551561, 18446744073709551543
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
