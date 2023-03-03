/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    27390, 59565, 12265, 23952, 18187, 35218, 64509, 45049, 7250, 53565, 10082, 29579, 39393, 11185, 17524, 1573
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    15555, 48121, 2183, 45141, 11850, 23682, 7243, 56717, 21959, 49402, 27396, 3765, 41790, 1482, 29274, 36246
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    55488, 4134, 10468, 42220, 56710, 12598, 49585, 13860, 52753, 16419, 19648, 29761, 58003, 57005, 50843, 47939
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    42945, 107686, 14448, 69093, 30037, 58900, 71752, 101766, 29210, 102968, 37478, 33345, 81183, 12668, 46799, 37820
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
