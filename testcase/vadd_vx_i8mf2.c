/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    133, 208, 155, 164, 75, 218, 241, 179, 188, 97, 59, 28, 93, 15, 210, 22
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    167, 108, 239, 62, 167, 34, 48, 221, 194, 212, 40, 177, 142, 76, 74, 119
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8mf2_t __riscv_vle8_v_i8mf2 (*in1, vl);
    vint8mf2_t __riscv_vle8_v_i8mf2 (*in2, vl);
    vint8mf2_t __riscv_vle8_v_i8mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8mf2_t out_data = __riscv_vadd_vx_i8mf2 (data1, data2, vl)
        vint8mf2_t __riscv_vse8_v_i8mf2 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    300, 316, 394, 226, 242, 252, 289, 400, 382, 309, 99, 205, 235, 91, 284, 141
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
