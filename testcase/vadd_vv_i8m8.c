/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    98, 52, 49, 10, 195, 113, 98, 34, 227, 99, 116, 177, 8, 64, 59, 2
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    243, 170, 200, 208, 197, 97, 178, 148, 97, 57, 245, 163, 229, 22, 172, 41
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8m8_t __riscv_vle8_v_i8m8 (*in1, vl);
    vint8m8_t __riscv_vle8_v_i8m8 (*in2, vl);
    vint8m8_t __riscv_vle8_v_i8m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8m8_t out_data = __riscv_vadd_vv_i8m8 (data1, data2, vl)
        vint8m8_t __riscv_vse8_v_i8m8 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    341, 222, 249, 218, 392, 210, 276, 182, 324, 156, 361, 340, 237, 86, 231, 43
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
