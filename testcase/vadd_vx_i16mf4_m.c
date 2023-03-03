/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    48961, 64014, 41585, 39132, 61897, 38974, 61613, 28322, 37423, 32394, 40424, 18476, 53013, 46935, 28666, 40857
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    9861, 45097, 14340, 62213, 50061, 32631, 13165, 52387, 22753, 45965, 30178, 3619, 57699, 15886, 20405, 34105
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    38932, 25478, 37217, 36878, 37629, 59112, 31636, 25072, 19328, 51417, 42024, 42427, 48561, 901, 23446, 22645
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    38932, 109111, 37217, 36878, 37629, 71605, 74778, 80709, 19328, 78359, 70602, 22095, 48561, 62821, 23446, 74962
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
