/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    1403, 20589, 4254, 2398, 38154, 15412, 31101, 36950, 59608, 22865, 36196, 378, 41832, 27261, 8705, 37389
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    34545, 18582, 4604, 38873, 45921, 54828, 48678, 22572, 64213, 52346, 12954, 13878, 19321, 20727, 23933, 43164
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    55199, 57911, 23515, 1680, 58556, 46905, 29833, 36629, 52171, 19999, 14945, 39529, 5065, 14990, 30953, 8669
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -33142, 2007, -350, -36476, -7768, -39416, -17577, 14378, -4606, -29482, 23242, -13500, 22510, 6534, -15228, -5775
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
