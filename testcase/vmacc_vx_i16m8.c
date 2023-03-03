/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    46727, 5876, 40825, 58927, 44240, 2335, 36381, 26314, 50584, 56997, 37684, 4026, 10121, 29502, 32762, 41140
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    38331, 23698, 43392, 39804, 4206, 59861, 20649, 62238, 37532, 52652, 15545, 45694, 31083, 3251, 42163, 58152
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8 (*in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8 (*in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8 (*out, vl);
    const int out_data[] = {
    18727, 26282, 9944, 2686, 33842, 46178, 2342, 2635, 60856, 27749, 23670, 24418, 61514, 63769, 13731, 15803
    };
    const int16_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i16m8 (data1_v, data2_v, vl);
        void vint16m8_t __riscv_vse16_v_i16 (int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    1791111364, 139275730, 1771488344, 2345532994, 186107282, 139821613, 751233611, 1637733367, 1898579544, 3001033793, 585821450, 183988462, 314652557, 95974771, 1381357937, 2392389083
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
