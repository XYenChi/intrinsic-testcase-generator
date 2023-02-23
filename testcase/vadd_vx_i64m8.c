/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    211, 16, 153, 117, 11, 159, 224, 2, 224, 31, 152, 115, 199, 231, 255, 183
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    224, 250, 229, 233, 48, 167, 214, 105, 53, 141, 95, 176, 91, 125, 135, 27
    };
    const int64_t *in2 = &data2[0];
    const int64_t out_data[16];
    int64_t *out = &out_data[0];
    vint64m8_t __riscv_vle64_v_i64m8 (*in1, vl);
    vint64m8_t __riscv_vle64_v_i64m8 (*in2, vl);
    vint64m8_t __riscv_vle64_v_i64m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint64m8_t out_data = __riscv_vadd_vx_i64m8 (data1, data2, vl)
        vint64m8_t __riscv_vse64_v_i64m8 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    435, 266, 382, 350, 59, 326, 438, 107, 277, 172, 247, 291, 290, 356, 390, 210
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
