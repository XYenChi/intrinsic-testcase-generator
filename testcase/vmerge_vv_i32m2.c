/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1318675523, 2111889418, 773870221, 615664622, 179215388, 443070849, 2545008753, 1992874945, 465867336, 3162900708, 1987917116, 3950399564, 179282658, 794226710, 3192770734, 676441274
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3085593058, 1513659934, 3208582015, 4168167019, 2882118038, 1009180081, 3259810191, 2633161788, 3543157621, 1910978562, 4283084792, 4255646386, 22358738, 1020073818, 4015526038, 1735493166
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    bool16_t masked[] = {
    0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i32m2 (data1_v, data2_v, size_t vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1318675523, 2111889418, 3208582015, 615664622, 2882118038, 1009180081, 2545008753, 2633161788, 465867336, 3162900708, 1987917116, 3950399564, 22358738, 1020073818, 4015526038, 1735493166
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
