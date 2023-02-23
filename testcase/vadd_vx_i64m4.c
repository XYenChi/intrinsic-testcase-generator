/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    230, 91, 128, 113, 39, 6, 54, 234, 58, 181, 190, 39, 79, 134, 234, 48
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    119, 79, 65, 176, 138, 154, 43, 96, 68, 182, 67, 63, 150, 0, 239, 175
    };
    const int64_t *in2 = &data2[0];
    const int64_t out_data[16];
    int64_t *out = &out_data[0];
    vint64m4_t __riscv_vle64_v_i64m4 (*in1, vl);
    vint64m4_t __riscv_vle64_v_i64m4 (*in2, vl);
    vint64m4_t __riscv_vle64_v_i64m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint64m4_t out_data = __riscv_vadd_vx_i64m4 (data1, data2, vl)
        vint64m4_t __riscv_vse64_v_i64m4 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    349, 170, 193, 289, 177, 160, 97, 330, 126, 363, 257, 102, 229, 134, 473, 223
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
