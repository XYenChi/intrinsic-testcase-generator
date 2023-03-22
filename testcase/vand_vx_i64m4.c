/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -112, 116, -40, -128, -2, -125, -54, 61, -69, 75, -101, 19, -107, 76, -12, 22
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    28, -82, -99, -98, -29, -19, -93, -63, -94, 113, -83, 30, 82, -27, -21, -3
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
        void __riscv_vse64_v_i64m4 (int64_t *out, vint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    28, 18446744073709551534, 18446744073709551517, 18446744073709551518, 18446744073709551587, 18446744073709551597, 18446744073709551523, 18446744073709551553, 18446744073709551522, 113, 18446744073709551533, 30, 82, 18446744073709551589, 18446744073709551595, 18446744073709551613
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
