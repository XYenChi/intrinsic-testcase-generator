/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    36694, 50196, 37339, 32963, 4454, 32420, 6609, 63937, 10061, 56214, 59988, 56459, 28773, 32933, 40550, 10355
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    36610, 45016, 41671, 38615, 56392, 44502, 35016, 58382, 46096, 52232, 12418, 9175, 4661, 3121, 48456, 26660
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    1391, 55651, 48554, 32281, 25929, 414, 16862, 7448, 23806, 826, 32380, 22545, 57262, 19413, 60348, 29369
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    1391, 95212, 79010, 71578, 60846, 76922, 16862, 7448, 56157, 108446, 32380, 22545, 57262, 19413, 89006, 37015
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
