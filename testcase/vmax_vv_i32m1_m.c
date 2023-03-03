/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2435684158, 3198330966, 2397736861, 1514105550, 3753131448, 2940916578, 1854419608, 2793626546, 2631165460, 2421610270, 519825432, 2092983619, 2901047114, 3594188774, 280161448, 2730889448
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3662913616, 791815573, 3539158170, 3641606505, 3264637800, 2398411090, 165758032, 3543719514, 3939575694, 2016133815, 1828295724, 921529821, 3146965669, 3120083723, 3365569052, 1248387363
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    3913143458, 3414190677, 960077971, 3660579734, 1060450121, 302085872, 2635399160, 3010543704, 2739279835, 1388140124, 2848971641, 4234924413, 663520920, 375892034, 2776149682, 859732529
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3913143458, 3198330966, 960077971, 3641606505, 3753131448, 2940916578, 2635399160, 3543719514, 3939575694, 1388140124, 2848971641, 2092983619, 663520920, 375892034, 3365569052, 2730889448
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
