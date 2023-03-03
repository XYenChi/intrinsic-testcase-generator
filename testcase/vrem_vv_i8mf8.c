/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    174, 241, 106, 18, 235, 253, 48, 95, 76, 103, 72, 183, 242, 15, 77, 92
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    164, 203, 185, 31, 44, 23, 90, 135, 139, 30, 63, 8, 126, 234, 58, 29
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
        out_v = __riscv_vrem_vv_i8mf8 (data1_v, data2_v, vl);
        void vint8mf8_t __riscv_vse8_v_i8 (int8mf8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    164, 203, 79, 13, 44, 23, 42, 40, 63, 30, 63, 8, 126, 9, 58, 29
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