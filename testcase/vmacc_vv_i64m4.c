/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    112, -28, 104, 36, 126, 34, -75, 94, 50, 88, 94, -69, 52, -29, 19, 37
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    110, -118, -105, -128, -90, 76, 101, -79, -34, -7, -78, 33, -75, 116, -117, -62
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4 (in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i64m4 (data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m4 (int64_t *out, vint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    12320, 3305, 18446744073709540696, 18446744073709547008, 18446744073709540277, 2584, 18446744073709544041, 18446744073709544191, 18446744073709549916, 18446744073709551000, 18446744073709544285, 18446744073709549340, 18446744073709547717, 18446744073709548252, 18446744073709549394, 18446744073709549323
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
