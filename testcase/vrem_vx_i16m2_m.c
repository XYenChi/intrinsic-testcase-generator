/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    55727, 27132, 47480, 36448, 58817, 63680, 38238, 51107, 43964, 52376, 64056, 34191, 26106, 1116, 58755, 17117
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    12509, 45006, 58784, 46825, 38931, 27791, 52096, 271, 14395, 19749, 51152, 56243, 13418, 13863, 63512, 48148
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    33429, 6807, 16166, 46014, 52560, 62158, 53504, 49926, 24467, 8567, 7397, 6304, 60567, 2281, 525, 26331
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    33429, 6807, 11304, 10377, 52560, 27791, 53504, 271, 14395, 8567, 51152, 22052, 60567, 471, 525, 13914
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
