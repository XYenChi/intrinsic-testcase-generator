/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -74, -14, -4, 44, -63, 53, -66, -58, -104, -24, -115, 71, 53, -108, -113, 112
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    111, -84, 11, 4, -114, -110, 25, 18, 5, -57, -95, -47, 125, -103, -18, -42
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
    111, 18446744073709551532, 11, 4, 18446744073709551502, 18446744073709551506, 25, 18, 5, 18446744073709551559, 18446744073709551521, 18446744073709551569, 125, 18446744073709551513, 18446744073709551598, 18446744073709551574
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
