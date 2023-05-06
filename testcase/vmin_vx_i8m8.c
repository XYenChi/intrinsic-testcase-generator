/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -25, 121, -126, -17, -96, -104, 2, 80, -97, 59, -17, -52, -79, 115, 41, 101
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    96, -55, -60, -35, 27, 7, -68, -48, -100, 36, 59, 7, -5, -97, 69, 52
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8 (in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8 (in2, vl);
    vint8m8_t out_v = __riscv_vle8_v_i8m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i8m8 (data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m8 (int8_t *out, vint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    96, 121, 196, 239, 27, 7, 2, 80, 159, 59, 59, 7, 251, 115, 69, 101
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
