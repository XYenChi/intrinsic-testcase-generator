/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    97, 80, 86, 76, 111, 13, 231, 211, 127, 64, 13, 82, 137, 170, 61, 79
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    156, 155, 189, 20, 91, 213, 114, 234, 187, 195, 217, 253, 29, 125, 67, 231
    };
    const int32_t *in2 = &data2[0];
    const int32_t out_data[16];
    int32_t *out = &out_data[0];
    vint32m4_t __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint32m4_t out_data = __riscv_vadd_vx_i32m4 (data1, data2, vl)
        vint32m4_t __riscv_vse32_v_i32m4 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    253, 235, 275, 96, 202, 226, 345, 445, 314, 259, 230, 335, 166, 295, 128, 310
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
