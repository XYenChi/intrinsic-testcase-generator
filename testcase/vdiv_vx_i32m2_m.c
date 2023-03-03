/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1420624856, 1280341069, 3893191566, 1369169663, 3771146399, 2998429380, 3323879233, 3741908703, 1849545249, 3928927795, 1797526837, 588320341, 3281554468, 4127755441, 1050887009, 704401662
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    569999367, 1386483350, 1100385395, 3309921026, 739176750, 2733419880, 3170347418, 1002924683, 2287552403, 3905937868, 880095100, 3008092687, 3446017249, 1603614570, 2059198313, 1689627000
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    4029983530, 1385045668, 2534703624, 1673895797, 2403857946, 790512536, 3324945537, 3670920230, 3238493551, 2345563299, 4264163187, 2991624337, 1696100177, 670429619, 2567688198, 1416094952
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4029983530, 1, 0, 1673895797, 2403857946, 790512536, 0, 3670920230, 1, 0, 0, 5, 1, 670429619, 2567688198, 1416094952
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
