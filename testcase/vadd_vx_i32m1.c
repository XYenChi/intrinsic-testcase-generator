/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    152, 170, 210, 12, 77, 107, 84, 27, 2, 233, 211, 192, 134, 225, 58, 235
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    114, 168, 140, 208, 241, 17, 217, 147, 90, 8, 96, 130, 221, 237, 150, 104
    };
    const int32_t *in2 = &data2[0];
    const int32_t out_data[16];
    int32_t *out = &out_data[0];
    vint32m1_t __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint32m1_t out_data = __riscv_vadd_vx_i32m1 (data1, data2, vl)
        vint32m1_t __riscv_vse32_v_i32m1 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    266, 338, 350, 220, 318, 124, 301, 174, 92, 241, 307, 322, 355, 462, 208, 339
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
