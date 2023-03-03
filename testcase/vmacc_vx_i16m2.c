/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    43332, 39, 26102, 15619, 23850, 40071, 34882, 34683, 209, 40869, 11362, 39558, 35811, 55900, 11039, 51744
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    32319, 2094, 62523, 52108, 31013, 31445, 51970, 15089, 57958, 36365, 27001, 28919, 17844, 51123, 33546, 26886
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (*in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (*in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2 (*out, vl);
    const int out_data[] = {
    45946, 27250, 44256, 54591, 4441, 26879, 29475, 47858, 47399, 55400, 25384, 45100, 38796, 45581, 42509, 10733
    };
    const int16_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i16m2 (data1_v, data2_v, vl);
        void vint16m2_t __riscv_vse16_v_i16 (int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    1400492854, 108916, 1632019602, 813929443, 739664491, 1260059474, 1812847015, 523379645, 12160621, 1486256585, 306810746, 1144022902, 639050280, 2857821281, 370356803, 1391199917
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
