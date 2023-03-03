/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1665061722, 4146874532, 1387759948, 3384388169, 148184857, 1693526956, 60746108, 3694973539, 645720791, 2350454971, 4247151019, 618114806, 2054527645, 194221341, 3237804906, 4284014262
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3195836031, 3330695395, 2023816245, 4096784135, 3718538272, 1340228227, 3280646747, 3840643431, 1859846533, 3641539086, 2671831329, 2955736354, 1535763616, 2609182234, 2544179503, 2784421155
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, size_t vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3195836031, 3330695395, 2023816245, 4096784135, 3718538272, 1340228227, 3280646747, 3840643431, 1859846533, 3641539086, 2671831329, 2955736354, 1535763616, 2609182234, 2544179503, 2784421155
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
