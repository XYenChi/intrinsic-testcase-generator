/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -50, -5, -104, 82, 17, 4, 23, -101, 19, 21, -97, -88, -109, -22, -124, 48
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    86, -24, 116, -80, 69, -30, -104, 19, -105, 122, -25, 35, -25, 33, 100, -112
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4 (*in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4 (*in2, vl);
    vint8m4_t out_v = __riscv_vle8_v_i8m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u8m4 (data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m4 (int8_t *out, vint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    -126, -133, -170, -46, 56, 73, 89, -145, 111, 45, 1, -146, 1, -105, -27, -80
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
