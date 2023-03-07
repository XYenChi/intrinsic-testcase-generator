/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2093746213, 413253401, 550621120, -1507870701, 571375093, 1411956926, 611208073, 365094213, -1997356834, 562600587, -497662368, 1424976201, 309987054, 1796445875, -427115752, 2050748011
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1014562274, -1423601784, 34726318, 350506848, -1217532609, -2097764838, -944570460, 1827775926, -1717704154, 1803838403, 1260809623, -38880270, -1174806989, 83881359, -1514145306, -483879858
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m2 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2876796420, 249043969, 297534696, -940609827, 245654355, 182037750, 370274097, 249578660, -1804927665, -1558748695, -2063037423, 1347526155, 99789227, 2075753484, -428654606, 1776401276
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
