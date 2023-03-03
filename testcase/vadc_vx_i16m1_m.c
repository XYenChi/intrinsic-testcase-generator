/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    6500, 62466, 34020, 42227, 25608, 41138, 24794, 57931, 24498, 41213, 43707, 53561, 63401, 36199, 24124, 19818
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    25295, 25109, 55823, 27196, 31788, 23543, 57840, 43430, 51954, 18538, 44033, 29835, 21258, 31850, 27882, 57582
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    26690, 64034, 2619, 966, 19657, 10389, 9685, 6900, 64214, 23666, 31250, 29593, 26838, 195, 24323, 56735
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    31795, 87576, 89844, 69423, 57396, 64682, 82635, 101362, 76452, 59751, 87740, 83396, 84659, 68050, 52007, 77400
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
