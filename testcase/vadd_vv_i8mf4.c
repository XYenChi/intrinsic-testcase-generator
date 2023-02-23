/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    238, 3, 26, 166, 19, 52, 40, 104, 243, 150, 181, 13, 151, 73, 22, 195
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    206, 182, 205, 130, 83, 44, 46, 27, 197, 139, 2, 30, 243, 141, 130, 247
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8mf4_t __riscv_vle8_v_i8mf4 (*in1, vl);
    vint8mf4_t __riscv_vle8_v_i8mf4 (*in2, vl);
    vint8mf4_t __riscv_vle8_v_i8mf4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8mf4_t out_data = __riscv_vadd_vv_i8mf4 (data1, data2, vl)
        vint8mf4_t __riscv_vse8_v_i8mf4 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    444, 185, 231, 296, 102, 96, 86, 131, 440, 289, 183, 43, 394, 214, 152, 442
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
