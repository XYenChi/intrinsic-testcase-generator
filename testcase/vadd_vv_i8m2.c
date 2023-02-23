/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    148, 69, 160, 28, 13, 148, 120, 164, 7, 249, 163, 89, 82, 226, 108, 72
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    129, 0, 161, 32, 68, 130, 221, 51, 52, 108, 124, 115, 41, 153, 223, 51
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8m2_t __riscv_vle8_v_i8m2 (*in1, vl);
    vint8m2_t __riscv_vle8_v_i8m2 (*in2, vl);
    vint8m2_t __riscv_vle8_v_i8m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8m2_t out_data = __riscv_vadd_vv_i8m2 (data1, data2, vl)
        vint8m2_t __riscv_vse8_v_i8m2 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    277, 69, 321, 60, 81, 278, 341, 215, 59, 357, 287, 204, 123, 379, 331, 123
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
