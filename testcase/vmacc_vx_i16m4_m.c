/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    42955, 26929, 26463, 13752, 19096, 46406, 49533, 64243, 44606, 62057, 36846, 48334, 17376, 24495, 53266, 53315
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    32318, 41226, 29965, 1143, 3367, 5780, 11098, 38950, 22951, 16917, 24848, 37854, 51985, 58172, 39916, 35609
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    9468, 64087, 28837, 53929, 52839, 31898, 24042, 50461, 11651, 44022, 41165, 4946, 7648, 18494, 31786, 6090
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    406697941, 1725798824, 763113531, 741631609, 1009013545, 1480258589, 1190872386, 3241766024, 519704507, 2731873255, 1516765590, 239059965, 132891649, 453010530, 1693113077, 324688351
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
