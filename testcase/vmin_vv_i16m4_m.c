/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    60627, 25838, 5930, 59857, 29393, 59258, 20264, 65354, 4792, 32945, 43731, 23863, 34818, 61090, 17164, 46192
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    46489, 59611, 59775, 48336, 30524, 27774, 38567, 11562, 36601, 30930, 23489, 34647, 52360, 61271, 52402, 46973
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    54996, 40427, 28342, 48900, 54716, 35044, 25557, 22637, 9474, 18185, 39281, 50840, 31797, 58787, 6746, 39553
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    60627, 40427, 28342, 59857, 30524, 59258, 38567, 22637, 36601, 18185, 39281, 50840, 52360, 61271, 6746, 39553
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
