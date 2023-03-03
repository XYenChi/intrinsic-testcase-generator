/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    823239022, 604516528, 1590669543, 634907718, 2938539507, 1951944635, 3787119996, 1203452593, 2915853380, 3338503438, 157933820, 3333236675, 789828741, 3887440436, 1712809869, 2564641646
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3249180597, 3860817584, 1292075842, 3402655361, 2266121682, 4112534371, 3697544702, 3441715607, 1284767086, 1635809527, 2391879466, 3113210834, 41530936, 612621881, 3666177592, 4014798621
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3249180597, 3860817584, 1590669543, 3402655361, 2938539507, 4112534371, 3787119996, 3441715607, 2915853380, 3338503438, 2391879466, 3333236675, 789828741, 3887440436, 3666177592, 4014798621
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
