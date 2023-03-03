/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    9, 154, 106, 85, 85, 36, 79, 173, 179, 237, 185, 22, 22, 2, 51, 164
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    174, 85, 88, 217, 45, 97, 223, 34, 46, 103, 48, 226, 245, 74, 31, 213
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf8(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8 (*in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8 (*in2, vl);
    vint8mf8_t out_v = __riscv_vle8_v_i8mf8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vv_i8mf8 (data1_v, data2_v, mask, vl);
        void vint8mf8_t __riscv_vse8_v_i8 (int8mf8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    183, 239, 194, 302, 130, 133, 302, 207, 225, 340, 233, 248, 267, 76, 82, 377
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
