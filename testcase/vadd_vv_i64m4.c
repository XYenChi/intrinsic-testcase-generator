/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    253, 179, 253, 86, 91, 72, 33, 119, 58, 225, 251, 105, 41, 88, 102, 47
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    245, 124, 104, 252, 5, 68, 157, 56, 151, 254, 36, 135, 39, 250, 96, 193
    };
    const int64_t *in2 = &data2[0];
    const int64_t out_data[16];
    int64_t *out = &out_data[0];
    vint64m4_t __riscv_vle64_v_i64m4 (*in1, vl);
    vint64m4_t __riscv_vle64_v_i64m4 (*in2, vl);
    vint64m4_t __riscv_vle64_v_i64m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint64m4_t out_data = __riscv_vadd_vv_i64m4 (data1, data2, vl)
        vint64m4_t __riscv_vse64_v_i64m4 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    498, 303, 357, 338, 96, 140, 190, 175, 209, 479, 287, 240, 80, 338, 198, 240
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
