/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    173, 52, 103, 180, 5, 221, 46, 199, 142, 177, 16, 46, 163, 130, 114, 159
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    211, 235, 197, 164, 51, 35, 42, 113, 73, 217, 41, 159, 104, 193, 16, 250
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8m8_t __riscv_vle8_v_i8m8 (*in1, vl);
    vint8m8_t __riscv_vle8_v_i8m8 (*in2, vl);
    vint8m8_t __riscv_vle8_v_i8m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8m8_t out_data = __riscv_vadd_vx_i8m8 (data1, data2, vl)
        vint8m8_t __riscv_vse8_v_i8m8 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    384, 287, 300, 344, 56, 256, 88, 312, 215, 394, 57, 205, 267, 323, 130, 409
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
