/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    106, 193, 89, 146, 143, 240, 255, 96, 6, 167, 90, 44, 248, 102, 235, 149
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    100, 38, 246, 110, 166, 160, 84, 243, 80, 82, 1, 50, 73, 59, 84, 16
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8mf4_t __riscv_vle8_v_i8mf4 (*in1, vl);
    vint8mf4_t __riscv_vle8_v_i8mf4 (*in2, vl);
    vint8mf4_t __riscv_vle8_v_i8mf4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8mf4_t out_data = __riscv_vadd_vx_i8mf4 (data1, data2, vl)
        vint8mf4_t __riscv_vse8_v_i8mf4 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    206, 231, 335, 256, 309, 400, 339, 339, 86, 249, 91, 94, 321, 161, 319, 165
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
