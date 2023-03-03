/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    58636, 43039, 5989, 60039, 58149, 36759, 39976, 14675, 2564, 11349, 27992, 12553, 50564, 40969, 41700, 16763
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    55317, 23459, 36953, 22038, 3744, 45248, 17889, 60266, 44320, 8935, 43749, 15307, 28357, 1004, 12737, 65483
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    28606, 28499, 25801, 22748, 57435, 17480, 57135, 6273, 41681, 48415, 63554, 37162, 8557, 11625, 61337, 30885
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    55317, 23459, 25801, 22038, 3744, 8489, 57135, 6273, 41681, 48415, 15757, 2754, 28357, 1004, 61337, 15194
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
