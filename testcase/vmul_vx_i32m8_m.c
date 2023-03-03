/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4146760737, 416424861, 3275579123, 2216037080, 2201042884, 1369916515, 229053650, 635935695, 2315241346, 2968317484, 744421929, 355905208, 1126047095, 3161640967, 1919455258, 2722874920
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1371104594, 4054327403, 1887522862, 1148351549, 1743406367, 441303564, 2421854529, 1469362119, 497734418, 1343204790, 3503096681, 535260560, 2459286904, 3093266852, 3506503919, 3493349992
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    2820676689, 255620632, 31711125, 3325014621, 2627954010, 4256845222, 3041242152, 2125402652, 202330637, 2743345949, 4168813837, 2339042268, 3474943981, 2721798304, 1476563458, 153901339
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2820676689, 1688322725242765983, 6182730480952410026, 2544789613459436920, 2627954010, 4256845222, 554734619636480850, 2125402652, 1152375303880846628, 2743345949, 2607781988743517649, 190502020940996480, 3474943981, 2721798304, 6730577384522156102, 153901339
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
