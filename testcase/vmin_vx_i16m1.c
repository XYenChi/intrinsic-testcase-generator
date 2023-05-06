/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -106, 2, -54, -41, 80, -120, 13, -89, 112, -36, -107, 96, -57, 64, 8, -66
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    86, 53, -92, -40, -81, -3, -124, 89, -42, 1, -2, 86, 81, 114, -14, 82
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1 (in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1 (in2, vl);
    vint16m1_t out_v = __riscv_vle16_v_i16m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i16m1 (data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m1 (int16_t *out, vint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    86, 53, 65482, 65496, 80, 65533, 13, 89, 112, 1, 65534, 96, 81, 114, 8, 82
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
