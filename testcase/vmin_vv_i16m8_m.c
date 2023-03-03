/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    19488, 12758, 13687, 60048, 40451, 57640, 45386, 42479, 40405, 28087, 62748, 32100, 30256, 26410, 1223, 51500
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    30238, 17070, 12585, 27641, 10321, 58218, 36670, 6604, 47575, 55339, 45889, 52080, 47948, 40125, 38272, 7369
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    57657, 40425, 37949, 15953, 18774, 16860, 31953, 59859, 57872, 17298, 17089, 60877, 4378, 58322, 11381, 24277
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    57657, 40425, 37949, 60048, 40451, 16860, 45386, 42479, 47575, 55339, 62748, 60877, 47948, 40125, 38272, 51500
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
