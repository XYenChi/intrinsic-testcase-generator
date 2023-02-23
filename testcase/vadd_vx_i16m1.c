/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    140, 205, 14, 50, 82, 62, 242, 89, 49, 175, 149, 69, 222, 212, 30, 243
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    219, 179, 87, 142, 66, 102, 36, 21, 145, 184, 94, 253, 127, 114, 240, 30
    };
    const int16_t *in2 = &data2[0];
    const int16_t out_data[16];
    int16_t *out = &out_data[0];
    vint16m1_t __riscv_vle16_v_i16m1 (*in1, vl);
    vint16m1_t __riscv_vle16_v_i16m1 (*in2, vl);
    vint16m1_t __riscv_vle16_v_i16m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint16m1_t out_data = __riscv_vadd_vx_i16m1 (data1, data2, vl)
        vint16m1_t __riscv_vse16_v_i16m1 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    359, 384, 101, 192, 148, 164, 278, 110, 194, 359, 243, 322, 349, 326, 270, 273
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
