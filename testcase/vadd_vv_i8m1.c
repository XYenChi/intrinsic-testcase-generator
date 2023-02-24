/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    84, 116, 40, 127, 246, 74, 218, 62, 201, 156, 247, 248, 200, 168, 139, 143
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    89, 31, 215, 13, 36, 133, 0, 177, 66, 214, 166, 25, 57, 72, 147, 118
    };
    const int8_t *in2 = &data2[0];
    size_t vl = vsetvl_e8m1(64);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m1_t __riscv_vle8_v_i8m1 (const int8_t *in1, size_t vl);
    vint8m1_t __riscv_vle8_v_i8m1 (const int8_t *in2, size_t vl);
    vint8m1_t __riscv_vle8_v_i8m1 (const int8_t *out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        vint8m1_t out_data = __riscv_vadd_vv_i8m1 (data1, data2, vl);
        vint8m1_t __riscv_vse8_v_i8m1 (*out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    173, 147, 255, 140, 282, 207, 218, 239, 267, 370, 413, 273, 257, 240, 286, 261
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
