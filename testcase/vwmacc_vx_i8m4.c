/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -116, 84, -20, 121, -89, 19, 27, -47, -119, 37, -81, -79, -59, 19, -44, 124
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -110, 77, -19, -66, -62, -17, 86, 26, -80, -107, 95, 96, 10, 65, -58, -31
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4 (in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4 (in2, vl);
    vint8m4_t out_v = __riscv_vle8_v_i8m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vwmacc_vx_i8m4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m4 (int8_t *out, vint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    217, 68, 124, 206, 142, 190, 19, 58, 49, 137, 241, 96, 178, 211, 248, 252
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
