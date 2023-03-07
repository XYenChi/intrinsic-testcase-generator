/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    39, 12, 124, 37, -104, 68, -5, -2, 112, 126, -67, 79, -27, 34, -30, 117
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -75, 19, 111, -125, 111, 72, 106, -72, 111, -122, -33, -88, 77, 50, -98, 127
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8 (*in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8 (*in2, vl);
    vint8mf8_t out_v = __riscv_vle8_v_i8mf8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u8mf8 (data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf8 (int8_t *out, vint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    82, 117, 220, 103, -121, -46, -94, -108, 125, 27, 42, 200, 8, 156, -17, 70
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
