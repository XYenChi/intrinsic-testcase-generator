/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1042213117, 1567309217, 1852743503, 3409145375, 3567072090, 3282799880, 390433930, 3279633007, 2430918359, 4016668388, 924164395, 2562697402, 1160663020, 2184759630, 3100393056, 495462644
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2359310820, 122742549, 2150385869, 2682433284, 2454069905, 3574361506, 3195302587, 4122464955, 801397396, 3398213169, 2523347849, 4005979647, 4015710110, 1973316602, 4040980588, 1594346049
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    1770977133, 4251095107, 1490402884, 1945681048, 1340513228, 106298706, 336731490, 302748507, 2001544233, 2391727075, 865133389, 2841942619, 1746683287, 414940100, 1420717648, 4141672639
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1770977133, 1567309217, 1490402884, 3409145375, 3567072090, 106298706, 3195302587, 302748507, 2430918359, 4016668388, 2523347849, 4005979647, 1746683287, 2184759630, 1420717648, 1594346049
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
