/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    180, 118, 67, 114, 23, 35, 72, 116, 236, 203, 59, 63, 66, 71, 140, 213
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    25, 92, 14, 187, 73, 215, 115, 185, 87, 40, 169, 177, 20, 15, 64, 248
    };
    const int64_t *in2 = &data2[0];
    const int64_t out_data[16];
    int64_t *out = &out_data[0];
    vint64m2_t __riscv_vle64_v_i64m2 (*in1, vl);
    vint64m2_t __riscv_vle64_v_i64m2 (*in2, vl);
    vint64m2_t __riscv_vle64_v_i64m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint64m2_t out_data = __riscv_vadd_vx_i64m2 (data1, data2, vl)
        vint64m2_t __riscv_vse64_v_i64m2 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    205, 210, 81, 301, 96, 250, 187, 301, 323, 243, 228, 240, 86, 86, 204, 461
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
