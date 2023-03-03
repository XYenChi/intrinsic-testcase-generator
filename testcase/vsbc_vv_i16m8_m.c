/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    26139, 37644, 15655, 12980, 5172, 38225, 9824, 50173, 41961, 13892, 34682, 62235, 61140, 36620, 1587, 15484
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    47312, 22453, 28184, 22053, 34848, 41195, 18536, 2482, 34283, 22497, 29985, 36567, 33302, 33186, 26676, 16940
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    34642, 748, 13903, 15350, 19206, 14650, 783, 5378, 16855, 9119, 56955, 64256, 46571, 36286, 17411, 16993
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -21173, 15190, -12530, -9074, -29676, -2971, -8713, 47690, 7678, -8606, 4697, 25667, 27837, 3433, -25090, -1457
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
