/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3450830222, 3021038441, 800739147, 2263571617, 3358216610, 290709771, 2205119569, 3725110893, 1425726810, 97986517, 3024862320, 2968027991, 2601847968, 794527860, 3770525679, 4172631147
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2726899771, 4173648505, 3145189894, 3466197415, 3777955757, 484997151, 2883078669, 111860973, 794836354, 3191804564, 1413828496, 379464548, 2644347789, 3363673181, 2634377579, 2070504805
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    1766767927, 332126957, 1619138560, 4285519521, 780901755, 1794789843, 2119478746, 1242741334, 3060851641, 2052174228, 3981161307, 1126533848, 3432840684, 4144679917, 924447594, 2425020054
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1766767927, 332126957, -2344450747, 4285519521, 780901755, 1794789843, 2119478746, 3613249920, 630890456, -3093818047, 1611033824, 2588563443, 3432840684, -2569145321, 1136148100, 2425020054
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
