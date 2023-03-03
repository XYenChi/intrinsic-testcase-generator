/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    28044, 28726, 3417, 46447, 61197, 57573, 14174, 59184, 12037, 64386, 4722, 25046, 52478, 26402, 7707, 6991
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    39220, 42259, 49052, 63804, 49122, 2225, 19253, 7040, 15138, 35210, 4153, 21514, 9222, 9011, 37298, 28788
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    43496, 19831, 29930, 27559, 34664, 53937, 55401, 15549, 13213, 23610, 32249, 3863, 10405, 46940, 55105, 52653
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -11176, -13533, -45635, 27559, 34664, 55348, 55401, 15549, 13213, 23610, 569, 3863, 43256, 46940, -29591, 52653
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
