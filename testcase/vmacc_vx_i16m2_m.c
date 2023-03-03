/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    26188, 31792, 41917, 29171, 52207, 251, 8280, 37546, 44524, 41610, 21771, 29176, 58503, 14584, 41894, 18044
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    44261, 10403, 30398, 17697, 10895, 262, 7686, 12367, 10744, 44844, 43651, 50184, 39391, 3302, 20206, 63632
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    26632, 15484, 9241, 16833, 62662, 56658, 3722, 5503, 36905, 63996, 38938, 9192, 29051, 24648, 56552, 34038
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    697438816, 492267329, 387354997, 491035443, 3271395034, 14221159, 30818161, 206615638, 1643158221, 2662873561, 847719198, 268185793, 1699570654, 359466433, 2369189489, 614181673
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
