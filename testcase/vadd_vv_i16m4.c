/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    198, 113, 198, 113, 125, 231, 209, 212, 196, 70, 105, 227, 83, 84, 238, 175
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    131, 137, 76, 43, 101, 150, 150, 233, 130, 199, 115, 19, 248, 92, 235, 140
    };
    const int16_t *in2 = &data2[0];
    const int16_t out_data[16];
    int16_t *out = &out_data[0];
    vint16m4_t __riscv_vle16_v_i16m4 (*in1, vl);
    vint16m4_t __riscv_vle16_v_i16m4 (*in2, vl);
    vint16m4_t __riscv_vle16_v_i16m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint16m4_t out_data = __riscv_vadd_vv_i16m4 (data1, data2, vl)
        vint16m4_t __riscv_vse16_v_i16m4 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    329, 250, 274, 156, 226, 381, 359, 445, 326, 269, 220, 246, 331, 176, 473, 315
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
