/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    38025, 60815, 29967, 34694, 32821, 28059, 35663, 49648, 7699, 56105, 6663, 56678, 53592, 30379, 49553, 7109
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    28831, 4527, 20745, 59777, 18774, 53472, 50686, 56133, 58248, 63343, 56852, 61894, 35873, 60113, 28652, 61947
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    42414, 44567, 25537, 9693, 12696, 29346, 32798, 41709, 1659, 18431, 52951, 39760, 36731, 15202, 15276, 10035
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    1612792351, 2710342105, 765267280, 336288942, 416695416, 823419415, 1169675075, 2070768432, 12772642, 1034071256, 352812513, 2253517281, 1968487752, 461821559, 756971628, 71338815
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
