/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -105, 13, 42, -107, 76, -69, -55, -126, 6, 9, 50, -24, -110, -80, 11, 63
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    47, -67, -31, 13, 30, 62, -65, -120, 124, -77, 9, 92, 9, 61, -2, -101
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
        out_v = __riscv_vor_vx_i64m8 (data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m8 (int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709551551, 18446744073709551549, 18446744073709551595, 18446744073709551517, 94, 18446744073709551551, 18446744073709551615, 18446744073709551498, 126, 18446744073709551547, 59, 18446744073709551612, 18446744073709551515, 18446744073709551549, 18446744073709551615, 18446744073709551551
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
