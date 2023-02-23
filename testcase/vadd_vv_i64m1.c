/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    199, 239, 195, 121, 77, 48, 49, 15, 137, 196, 202, 26, 189, 54, 46, 133
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    94, 61, 93, 157, 19, 236, 125, 173, 27, 104, 50, 133, 15, 187, 63, 81
    };
    const int64_t *in2 = &data2[0];
    const int64_t out_data[16];
    int64_t *out = &out_data[0];
    vint64m1_t __riscv_vle64_v_i64m1 (*in1, vl);
    vint64m1_t __riscv_vle64_v_i64m1 (*in2, vl);
    vint64m1_t __riscv_vle64_v_i64m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint64m1_t out_data = __riscv_vadd_vv_i64m1 (data1, data2, vl)
        vint64m1_t __riscv_vse64_v_i64m1 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    293, 300, 288, 278, 96, 284, 174, 188, 164, 300, 252, 159, 204, 241, 109, 214
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
