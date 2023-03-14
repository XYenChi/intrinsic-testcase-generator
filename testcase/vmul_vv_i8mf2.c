/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -95, -126, -52, 27, 21, -45, 48, 10, 27, 43, -19, -43, 46, -36, 119, -116
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -107, -47, -24, 55, -54, -49, 123, -83, 10, -65, 118, 33, 20, 62, 107, 20
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2 (in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2 (in2, vl);
    vint8mf2_t out_v = __riscv_vle8_v_i8mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i8mf2 (data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf2 (int8_t *out, vint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    181, 34, 224, 205, 146, 157, 16, 194, 14, 21, 62, 117, 152, 72, 189, 240
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
