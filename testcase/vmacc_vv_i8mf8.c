/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    92, -90, -102, 92, 37, 10, -1, 12, 53, -28, 111, -59, -24, 78, 40, -66
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    46, -67, -81, 29, 14, 46, 13, 104, 5, -102, 81, -110, 35, -75, -47, -46
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8 (in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8 (in2, vl);
    vint8mf8_t out_v = __riscv_vle8_v_i8mf8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i8mf8 (data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf8 (int8_t *out, vint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    137, 142, 70, 108, 7, 205, 243, 225, 9, 41, 31, 90, 184, 39, 168, 221
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
