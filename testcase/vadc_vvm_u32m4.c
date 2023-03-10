/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2547499615, 1559409088, 1735353718, 1989536936, 1202556226, 4293119363, 439673410, 3340372541, 2541771781, 215309118, 4047468707, 754957442, 2219956714, 2795294863, 1809488759, 23620878
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2431225868, 3902613021, 109987995, 199507270, 2171152097, 2745094257, 230012654, 1468385391, 428461584, 1149527719, 1597244496, 3627081900, 1177895493, 2311290646, 362918935, 2546927385
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    bool8_t masked[] = {
    0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4 (in1, vl);
    vuint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m4 (uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4978725483, 5462022110, 1845341713, 2189044206, 3373708324, 7038213620, 669686064, 4808757932, 2970233365, 1364836838, 5644713203, 4382039342, 3397852208, 5106585509, 2172407695, 2570548263
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
