/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    156, 80, 118, 248, 187, 239, 74, 83, 3, 116, 125, 229, 208, 27, 214, 113
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    157, 40, 207, 206, 174, 172, 52, 193, 230, 90, 209, 207, 253, 159, 183, 133
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf2(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2 (*in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2 (*in2, vl);
    vint8mf2_t out_v = __riscv_vle8_v_i8mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vx_i8mf2 (data1_v, data2_v, mask, vl);
        void vint8mf2_t __riscv_vse8_v_i8 (int8mf2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    313, 120, 325, 454, 361, 411, 126, 276, 233, 206, 334, 436, 461, 186, 397, 246
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
