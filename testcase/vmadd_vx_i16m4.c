/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -81, 19, -68, -36, -61, 102, 8, -54, 127, -61, 69, 52, -96, -15, -5, 8
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    82, 117, 119, 13, 117, 28, 117, 115, -21, -101, 93, -34, 98, 34, -117, -115
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4 (in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4 (in2, vl);
    vint16m4_t out_v = __riscv_vle16_v_i16m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmadd_vx_i16m4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m4 (int16_t *out, vint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    1, 136, 51, 13, 56, 130, 125, 61, 106, 65374, 93, 18, 98, 19, 65419, 65421
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
