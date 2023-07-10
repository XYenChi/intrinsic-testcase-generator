/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    1704566269, 2759179444, 3583711535, 1785651994, 2117318042, 2905483194, 2927545228, 1368888893, 2342862056, 449950651, 3500210340, 1678515823, 4292298698, 949354933, 1264765540, 3554913677
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    1584690663, 1873916176, 3853978838, 4130696450, 1043192177, 4127525706, 4238707005, 3831027959, 736825506, 4147200873, 3950840206, 4232085809, 3061594936, 2506063012, 3223708573, 60873981
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2 (in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_u32mf2 (in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vx_u32mf2(op1, op2, vl);
        void __riscv_vse32_v_u32mf2 (uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    3289256932, 338128324, 3142723077, 1621381148, 3160510219, 2738041604, 2871284937, 904949556, 3079687562, 302184228, 3156083250, 1615634336, 3058926338, 3455417945, 193506817, 3615787658
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
    109143102, 3823852483, 4062766634, 2229569350, 2542517703, 748276141, 3135869449, 831268748, 3118235505, 27422654, 1677388806, 3999667810, 2544360872, 894870094, 3876904809, 3256661246
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    2875486622, 2243548982, 639735022, 1722758071, 3827196311, 4186344493, 218635345, 4161947234, 2552119711, 3292420016, 2212072258, 1959784666, 2951878558, 3340721370, 3387704219, 3351611274
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2 (in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_u32mf2 (in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32mf2 (uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    2984629724, 1772434169, 407534360, 3952327421, 2074746718, 639653338, 3354504794, 698248686, 1375387920, 3319842670, 3889461064, 1664485180, 1201272134, 4235591464, 2969641732, 2313305224
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
