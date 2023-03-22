/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -98, 55, -46, 57, -41, 126, 95, 13, 41, -29, -72, -54, -47, -74, -81, -49
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    107, 5, 69, 4, 122, -34, -117, -102, -61, 75, -115, -7, -31, -13, -51, -52
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmadd_vv_i16mf2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf2 (int16_t *out, vint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    107, 5, 69, 4, 122, 65502, 65419, 65434, 65475, 75, 65421, 65475, 65505, 65523, 65485, 65435
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
