/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    244, 100, 94, 143, 223, 175, 211, 76, 216, 9, 161, 86, 109, 17, 184, 181
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    121, 81, 200, 200, 147, 196, 169, 120, 236, 158, 147, 78, 29, 143, 1, 2
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8mf8_t __riscv_vle8_v_i8mf8 (*in1, vl);
    vint8mf8_t __riscv_vle8_v_i8mf8 (*in2, vl);
    vint8mf8_t __riscv_vle8_v_i8mf8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8mf8_t out_data = __riscv_vadd_vx_i8mf8 (data1, data2, vl)
        vint8mf8_t __riscv_vse8_v_i8mf8 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    365, 181, 294, 343, 370, 371, 380, 196, 452, 167, 308, 164, 138, 160, 185, 183
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
