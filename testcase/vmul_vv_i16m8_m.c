/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    24365, 45594, 20203, 39329, 59391, 2097, 29454, 58969, 37336, 26028, 56846, 49694, 55851, 55196, 27005, 59445
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    10451, 1884, 1404, 10018, 11993, 49431, 2183, 31740, 35550, 33818, 62118, 17733, 4025, 59587, 12962, 14570
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    22277, 61342, 35869, 64921, 40050, 21145, 58655, 29788, 54908, 42469, 4049, 13979, 63499, 52503, 52021, 9010
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    254638615, 61342, 35869, 64921, 712276263, 103656807, 58655, 1871676060, 1327294800, 42469, 4049, 881223702, 224800275, 3288964052, 350038810, 866113650
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
