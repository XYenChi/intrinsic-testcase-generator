/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    32465, 63392, 16956, 13946, 30407, 601, 53083, 39192, 3742, 46464, 10592, 31317, 13975, 9755, 27837, 18452
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    52685, 63096, 35939, 39704, 41415, 3355, 43840, 42076, 50832, 36428, 55514, 3574, 29964, 24829, 2297, 23653
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    63007, 12281, 53617, 61128, 9506, 64899, 28330, 9602, 21465, 21872, 24270, 53389, 64643, 4406, 22506, 31379
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    1, 0, 2, 2, 9506, 64899, 28330, 9602, 13, 21872, 24270, 0, 2, 4406, 0, 31379
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
