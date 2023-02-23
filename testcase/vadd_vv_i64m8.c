/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    192, 148, 198, 110, 44, 183, 110, 173, 129, 162, 209, 53, 59, 11, 178, 156
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    149, 62, 11, 177, 114, 60, 35, 167, 165, 7, 12, 96, 218, 116, 56, 172
    };
    const int64_t *in2 = &data2[0];
    const int64_t out_data[16];
    int64_t *out = &out_data[0];
    vint64m8_t __riscv_vle64_v_i64m8 (*in1, vl);
    vint64m8_t __riscv_vle64_v_i64m8 (*in2, vl);
    vint64m8_t __riscv_vle64_v_i64m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint64m8_t out_data = __riscv_vadd_vv_i64m8 (data1, data2, vl)
        vint64m8_t __riscv_vse64_v_i64m8 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    341, 210, 209, 287, 158, 243, 145, 340, 294, 169, 221, 149, 277, 127, 234, 328
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
