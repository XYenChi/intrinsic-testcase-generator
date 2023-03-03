/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2300144933, 1909545289, 1057632480, 36343712, 2067822674, 1526183760, 1374148400, 1115990727, 3273746061, 1439626222, 3299773992, 2694219901, 1630756888, 3934475362, 1315709731, 3440793525
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4016576994, 500649758, 2971822160, 421053039, 1225553899, 1218261486, 3040442654, 2241354202, 4105096762, 819002075, 4144516447, 1080775846, 2977938071, 4086817538, 3049488742, 640958078
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    const int out_data[] = {
    2658789208, 602042340, 2178416269, 1561283088, 360696683, 826194871, 3046544173, 2697413601, 3628644515, 2427759868, 1148495447, 2748756567, 3621732430, 3653700558, 3195467577, 4212872342
    };
    const int32_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    9238709223412260610, 956013387429932402, 3143095643378173069, 15302631947423856, 2534228140922002609, 1859290896192862231, 4178019411332397773, 2501330508051898455, 13439044358249998997, 1179056865470170518, 13675967582375341871, 2911847795562067813, 4856293024942415478, 16079482915904199314, 4012242015619815979, 2205404408791717292
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
