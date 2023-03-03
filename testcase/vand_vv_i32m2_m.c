/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1104020604, 2403965559, 3845336685, 4187004242, 445231445, 2830536210, 3063893, 3468879588, 697275998, 439611112, 2813693411, 1496354037, 3005536692, 2359734869, 2935693240, 4288452380
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3334104536, 2512122920, 2803066365, 2680295346, 2531111403, 2231279393, 1008246949, 3487924417, 1462390561, 3325687816, 3800292156, 4243626716, 2450465991, 2434909156, 738366291, 1929177174
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    497405474, 2789531710, 459812405, 1903757520, 111445008, 3454886572, 347890319, 1059447378, 4176706148, 3047772634, 1674737107, 1989973522, 2023267486, 2914557011, 1261563564, 3696520844
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3334104536, 2789531710, 459812405, 1903757520, 2531111403, 2231279393, 1008246949, 1059447378, 4176706148, 3047772634, 3800292156, 4243626716, 2450465991, 2914557011, 738366291, 1929177174
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
