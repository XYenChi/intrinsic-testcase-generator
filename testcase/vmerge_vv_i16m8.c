/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    18058, 59498, 50140, 25874, 27210, 16339, 20658, 4646, 27895, 38222, 34440, 32030, 20866, 37599, 28523, 38273
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    58484, 15747, 4837, 21199, 55706, 53054, 54228, 22820, 38465, 334, 51676, 45016, 20090, 39661, 50140, 24950
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    bool2_t masked[] = {
    0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8 (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i16m8 (data1_v, data2_v, size_t vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    18058, 59498, 4837, 25874, 55706, 53054, 54228, 4646, 38465, 38222, 51676, 45016, 20090, 39661, 50140, 24950
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
