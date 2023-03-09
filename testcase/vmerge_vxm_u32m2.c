/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1872607927, 1672421528, 4050706800, 758557088, 789802641, 3452773551, 434892712, 885468851, 2666820475, 1641884630, 2860264977, 48786927, 1696375196, 3069608674, 2810073824, 3561387369
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    461800025, 3513306707, 3530351729, 2869148841, 1077189262, 2564505511, 5634585, 3567133558, 1547093130, 3339801124, 3463535624, 899358853, 3132537475, 2483636687, 1814971152, 2104294372
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    bool16_t masked[] = {
    1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2 (in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m2 (uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    461800025, 3513306707, 4050706800, 758557088, 1077189262, 2564505511, 5634585, 885468851, 2666820475, 3339801124, 2860264977, 899358853, 1696375196, 2483636687, 1814971152, 2104294372
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
