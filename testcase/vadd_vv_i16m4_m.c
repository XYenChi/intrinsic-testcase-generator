/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    38224, 41458, 16575, 11793, 49450, 34286, 12170, 16198, 24336, 59295, 27528, 27222, 1607, 9845, 35947, 17957
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    50824, 11523, 9357, 15300, 54191, 37450, 34414, 35266, 55953, 17107, 53121, 36900, 708, 25635, 63749, 54298
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    31277, 49362, 63838, 44002, 17864, 42519, 28980, 431, 28023, 44049, 21828, 31495, 6645, 49286, 45617, 49365
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    89048, 49362, 25932, 27093, 103641, 42519, 46584, 431, 28023, 44049, 21828, 64122, 6645, 49286, 45617, 49365
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
