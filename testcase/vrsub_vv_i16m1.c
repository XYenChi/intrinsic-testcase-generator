/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -69, -75, 109, 95, 14, -51, -58, -3, -121, -116, -57, 122, 42, 13, 95, 79
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -20, 61, -72, 7, 2, 57, -4, -53, 81, -8, 118, 32, 65, -122, 60, 89
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
        out_v = __riscv_vrsub_vx_i16m1 (data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m1 (int16_t *out, vint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    49, 136, 65355, 65448, 65524, 108, 54, 65486, 202, 108, 175, 65446, 23, 65401, 65501, 10
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
