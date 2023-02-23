/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    109, 132, 238, 187, 182, 252, 117, 209, 182, 59, 196, 56, 58, 8, 253, 26
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    66, 200, 179, 121, 75, 56, 49, 197, 1, 59, 86, 126, 174, 254, 115, 44
    };
    const int32_t *in2 = &data2[0];
    const int32_t out_data[16];
    int32_t *out = &out_data[0];
    vint32m1_t __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint32m1_t out_data = __riscv_vadd_vv_i32m1 (data1, data2, vl)
        vint32m1_t __riscv_vse32_v_i32m1 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    175, 332, 417, 308, 257, 308, 166, 406, 183, 118, 282, 182, 232, 262, 368, 70
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
