/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    14628, 60033, 45214, 12552, 40141, 20910, 30339, 47910, 27402, 28687, 5310, 62572, 41282, 31288, 18378, 54706
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    42788, 28914, 35851, 61525, 6991, 58074, 9490, 60207, 39644, 37153, 60584, 21960, 34114, 7217, 21991, 2819
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    62838, 55069, 50720, 20607, 35166, 62195, 2651, 39942, 64538, 30199, 46470, 56058, 10063, 5726, 10903, 48675
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1
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
    57417, 88947, 81065, 74077, 47132, 78984, 39830, 108118, 67046, 65841, 65894, 84533, 75396, 38506, 40370, 57526
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
