/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    9, 247, 68, 234, 105, 187, 108, 84, 93, 131, 210, 49, 233, 31, 74, 108
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    51, 195, 45, 37, 199, 85, 201, 148, 117, 148, 186, 48, 192, 44, 180, 183
    };
    const int64_t *in2 = &data2[0];
    const int64_t out_data[16];
    int64_t *out = &out_data[0];
    vint64m2_t __riscv_vle64_v_i64m2 (*in1, vl);
    vint64m2_t __riscv_vle64_v_i64m2 (*in2, vl);
    vint64m2_t __riscv_vle64_v_i64m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint64m2_t out_data = __riscv_vadd_vv_i64m2 (data1, data2, vl)
        vint64m2_t __riscv_vse64_v_i64m2 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    60, 442, 113, 271, 304, 272, 309, 232, 210, 279, 396, 97, 425, 75, 254, 291
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
