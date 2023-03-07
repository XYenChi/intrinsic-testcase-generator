/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1463282303, 838111927, 15335422, 1994122549, 1024670335, -1622681514, 1270733580, -1973707065, 2075545577, -1664397789, -1670546902, 129478064, -1857677011, 900407128, -1636603140, 382008061
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1532629058, 379097475, -166976897, 1549722231, -943459959, -1158644009, -1677239199, -20645936, 473633373, -1741809706, 1410677421, -1064522154, -1111275748, -1682914962, 196011217, 1261437728
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int out_data[] = {
    761819078, -2019262828, -363611396, -1939812480, -339879483, 1668089669, -240053335, 1650665012, -1872703428, -167802283, 739934870, 995540576, -22058265, -233691513, -83561632, -2011616598
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m2 (bool32_t mask, int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    761819078, -2019262827, -363611396, -1939812480, -339879483, 1668089669, -240053334, 1650665012, -1872703428, -167802282, 739934871, 995540576, -22058265, -233691512, -83561632, -2011616598
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
