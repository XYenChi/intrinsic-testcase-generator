/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    30606, 38075, 3075, 6784, 52054, 28175, 28029, 61634, 46393, 52024, 22442, 32330, 733, 2384, 33271, 24720
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    64305, 59442, 34531, 20329, 14097, 30283, 4515, 59976, 29811, 34149, 21960, 55947, 56862, 61464, 37934, 7522
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8 (*in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8 (*in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i16m8 (data1_v, data2_v, vl);
        void vint16m8_t __riscv_vse16_v_i16 (int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    1968118830, 2263254150, 106182825, 137911936, 733805238, 853223525, 126550935, 3696560784, 1383021723, 1776567576, 492826320, 1808766510, 41679846, 146530176, 1262102114, 185943840
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
