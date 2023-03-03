/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    103, 185, 161, 203, 23, 68, 208, 215, 254, 16, 90, 133, 189, 85, 155, 131
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    37, 70, 252, 193, 180, 236, 119, 244, 202, 198, 241, 79, 96, 216, 96, 2
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m1(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1 (*in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1 (*in2, vl);
    vint8m1_t out_v = __riscv_vle8_v_i8m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vv_i8m1 (data1_v, data2_v, mask, vl);
        void vint8m1_t __riscv_vse8_v_i8 (int8m1_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    140, 255, 413, 396, 203, 304, 327, 459, 456, 214, 331, 212, 285, 301, 251, 133
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
