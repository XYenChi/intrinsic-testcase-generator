/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    836005324, 2945641774, 1855536793, 1869802934, 3485528837, 3700792871, 1779983906, 4216661681, 141106766, 1578197395, 618648980, 4239716408, 592965824, 1793848217, 2199926929, 3111575087
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3641699049, 3646619813, 1259377140, 1864465657, 2335338442, 3890656003, 560529638, 2362146193, 2838731194, 18508833, 3243829340, 4056018136, 4038400002, 4018314147, 311382185, 2932633896
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -2805693725, -700978039, 596159653, 5337277, 1150190395, -189863132, 1219454268, 1854515488, -2697624428, 1559688562, -2625180360, 183698272, -3445434178, -2224465930, 1888544744, 178941191
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
