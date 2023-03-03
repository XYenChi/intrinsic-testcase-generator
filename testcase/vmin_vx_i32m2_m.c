/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    748283387, 2980196987, 900797195, 36309078, 1349066563, 4030007858, 3781084893, 2522091049, 3009824524, 2449318729, 2377663177, 1917277930, 706468607, 3242572956, 1825982037, 243807523
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    177914037, 516825753, 4041646977, 2164200988, 2926960933, 932314981, 3113007357, 297721753, 2986174535, 1922261340, 3183910321, 3058490584, 4276239622, 968730239, 1316105474, 18526442
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    338896681, 761976936, 1693363032, 123952891, 3594472401, 1616644002, 902470674, 3237132988, 1331728607, 3251731909, 1045058062, 2451673726, 812347365, 442326878, 3642512843, 225555857
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    338896681, 2980196987, 1693363032, 2164200988, 2926960933, 4030007858, 902470674, 3237132988, 1331728607, 3251731909, 1045058062, 2451673726, 812347365, 3242572956, 3642512843, 243807523
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
