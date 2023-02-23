/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    223, 220, 109, 225, 57, 111, 180, 178, 181, 67, 162, 179, 126, 226, 2, 34
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    39, 192, 4, 0, 194, 47, 153, 79, 167, 192, 79, 205, 225, 88, 22, 171
    };
    const int32_t *in2 = &data2[0];
    const int32_t out_data[16];
    int32_t *out = &out_data[0];
    vint32m8_t __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint32m8_t out_data = __riscv_vadd_vx_i32m8 (data1, data2, vl)
        vint32m8_t __riscv_vse32_v_i32m8 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    262, 412, 113, 225, 251, 158, 333, 257, 348, 259, 241, 384, 351, 314, 24, 205
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
