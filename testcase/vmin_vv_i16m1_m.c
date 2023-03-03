/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    39102, 7677, 20989, 26713, 28242, 40696, 54077, 30404, 45098, 22904, 4282, 32875, 4374, 8007, 23173, 64577
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    34260, 57633, 25811, 52945, 37925, 20587, 13268, 38896, 47978, 32588, 57588, 32458, 40979, 19438, 42681, 64518
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    32675, 19569, 10535, 35147, 30089, 25238, 38492, 21373, 7249, 34038, 5112, 26745, 44926, 64354, 47597, 42570
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    39102, 57633, 10535, 35147, 30089, 40696, 38492, 21373, 47978, 32588, 57588, 26745, 44926, 64354, 42681, 42570
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
