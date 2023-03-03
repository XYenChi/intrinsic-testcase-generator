/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    2816, 56434, 51599, 30323, 11786, 35453, 42839, 55509, 23434, 4155, 42103, 46729, 39039, 10153, 9919, 1036
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    54818, 35509, 3930, 25941, 23643, 61014, 7240, 21710, 12145, 2632, 20393, 10230, 14102, 60974, 25753, 49574
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    40704, 15955, 51716, 745, 43771, 63913, 2702, 1745, 48595, 7186, 35468, 59696, 49711, 28303, 57607, 40252
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    57634, 15955, 55529, 745, 35429, 96467, 2702, 1745, 35579, 6787, 62496, 56959, 49711, 71127, 57607, 50610
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
