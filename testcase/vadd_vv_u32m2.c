/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    4092429192, 974349714, 1571300632, 1033266416, 3347836837, 1205326352, 4286445331, 2946873266, 2911398479, 789090128, 2387424813, 646982251, 1734225299, 3067896389, 737078525, 3093656999
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    2048770039, 2060149908, 4126940470, 4025596619, 1600290109, 898694385, 4040885084, 3560012865, 3466900369, 226969059, 1976084701, 4229590385, 2556683874, 2848761673, 3020980202, 2018640430
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2 (in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_u32m2 (in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vv_u32m2(op1, op2, vl);
        void __riscv_vse32_v_u32m2 (uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    1846231935, 3034499622, 1403273806, 763895739, 653159650, 2104020737, 4032363119, 2211918835, 2083331552, 1016059187, 68542218, 581605340, 4290909173, 1621690766, 3758058727, 817330133
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
/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    776619402, 653400037, 1188155691, 1084781334, 2206881202, 558728192, 1909023315, 2981996689, 1795949280, 3935674405, 2678625690, 3570566599, 2150539928, 3403050192, 43149734, 1478721155
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    319469007, 2247520293, 1651520091, 2003090461, 1909655142, 1840694685, 1364353901, 3839367898, 2762531391, 2333492381, 2255616163, 550123899, 726338237, 337490637, 1727048871, 79960102
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2 (in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_u32m2 (in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m2 (uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    1096088409, 2900920330, 2839675782, 3087871795, 4116536344, 2399422877, 3273377216, 2526397291, 263513375, 1974199490, 639274557, 4120690498, 2876878165, 3740540829, 1770198605, 1558681257
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
