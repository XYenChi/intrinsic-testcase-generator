/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    42613, 4229, 34994, 41285, 41275, 19164, 8439, 3473, 22178, 31528, 27620, 51065, 45962, 38509, 14393, 10654
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    45711, 16336, 31988, 6398, 31505, 43478, 35677, 27383, 57336, 18384, 11808, 42727, 22266, 33965, 51814, 29806
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    13682, 46314, 45340, 6922, 60939, 37817, 27634, 37419, 12709, 15672, 30429, 13102, 44897, 23186, 22869, 32356
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    13682, 46314, 31988, 6922, 31505, 37817, 27634, 3072, 12709, 18384, 11808, 42727, 22266, 23186, 8635, 8498
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
