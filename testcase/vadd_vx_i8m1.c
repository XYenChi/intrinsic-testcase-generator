/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    156, 0, 149, 54, 44, 86, 162, 43, 225, 198, 112, 68, 51, 133, 208, 121
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    207, 251, 58, 127, 116, 173, 65, 42, 125, 10, 234, 107, 127, 18, 239, 45
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8m1_t __riscv_vle8_v_i8m1 (*in1, vl);
    vint8m1_t __riscv_vle8_v_i8m1 (*in2, vl);
    vint8m1_t __riscv_vle8_v_i8m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8m1_t out_data = __riscv_vadd_vx_i8m1 (data1, data2, vl)
        vint8m1_t __riscv_vse8_v_i8m1 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    363, 251, 207, 181, 160, 259, 227, 85, 350, 208, 346, 175, 178, 151, 447, 166
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
