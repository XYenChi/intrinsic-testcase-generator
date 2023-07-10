/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    3833221010, 1095670893, 3840737414, 2412083536, 686053852, 3504287358, 2722842602, 1438352177, 3945642661, 1295187967, 3575245983, 1149262805, 3122782728, 240670019, 879871311, 75643562
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    2116837194, 4176324083, 987403056, 701638816, 1403881443, 457937850, 2010774956, 1945721953, 3121657229, 2555489149, 1006871663, 4270335834, 2045327247, 1761660120, 636430346, 1616196044
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4 (in1, vl);
    vuint32m4_t data2_v = __riscv_vle32_v_u32m4 (in2, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vv_u32m4(op1, op2, vl);
        void __riscv_vse32_v_u32m4 (uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    1655090908, 977027680, 533173174, 3113722352, 2089935295, 3962225208, 438650262, 3384074130, 2772332594, 3850677116, 287150350, 1124631343, 873142679, 2002330139, 1516301657, 1691839606
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
    2162291289, 3795189808, 890724565, 4227712627, 1925842899, 2384500602, 1274812967, 3534889842, 3187011305, 3410514360, 3057409189, 1287773563, 784685019, 2373183158, 2225975025, 1434397507
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    1700602162, 2733730125, 4244821441, 250646024, 2880272049, 861086851, 3329048322, 4166651802, 2524080074, 2020382219, 1543604065, 3504389526, 2560124252, 3869995390, 1974994719, 1136775031
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4 (in1, vl);
    vuint32m4_t data2_v = __riscv_vle32_v_u32m4 (in2, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m4 (uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    3862893451, 2233952637, 840578710, 183391355, 511147652, 3245587453, 308893993, 3406574348, 1416124083, 1135929283, 306045958, 497195793, 3344809271, 1948211252, 4200969744, 2571172538
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
