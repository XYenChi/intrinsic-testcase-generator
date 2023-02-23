/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    78, 211, 38, 213, 90, 112, 209, 218, 66, 14, 202, 124, 127, 59, 131, 110
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    6, 255, 56, 187, 139, 207, 197, 253, 65, 219, 64, 201, 213, 240, 39, 244
    };
    const int64_t *in2 = &data2[0];
    const int64_t out_data[16];
    int64_t *out = &out_data[0];
    vint64m1_t __riscv_vle64_v_i64m1 (*in1, vl);
    vint64m1_t __riscv_vle64_v_i64m1 (*in2, vl);
    vint64m1_t __riscv_vle64_v_i64m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint64m1_t out_data = __riscv_vadd_vx_i64m1 (data1, data2, vl)
        vint64m1_t __riscv_vse64_v_i64m1 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    84, 466, 94, 400, 229, 319, 406, 471, 131, 233, 266, 325, 340, 299, 170, 354
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
