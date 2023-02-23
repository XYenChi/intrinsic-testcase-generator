/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    171, 12, 130, 213, 94, 91, 65, 84, 230, 147, 26, 177, 36, 68, 24, 157
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    174, 105, 32, 139, 132, 95, 208, 27, 160, 29, 28, 190, 58, 190, 88, 108
    };
    const int16_t *in2 = &data2[0];
    const int16_t out_data[16];
    int16_t *out = &out_data[0];
    vint16m8_t __riscv_vle16_v_i16m8 (*in1, vl);
    vint16m8_t __riscv_vle16_v_i16m8 (*in2, vl);
    vint16m8_t __riscv_vle16_v_i16m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint16m8_t out_data = __riscv_vadd_vv_i16m8 (data1, data2, vl)
        vint16m8_t __riscv_vse16_v_i16m8 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    345, 117, 162, 352, 226, 186, 273, 111, 390, 176, 54, 367, 94, 258, 112, 265
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
