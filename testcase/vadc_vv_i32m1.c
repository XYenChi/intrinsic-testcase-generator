/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    907910980, 2290157062, 111216165, 3191816463, 2556226025, 3441718715, 2258596198, 910047221, 1504719245, 1849452839, 3010711670, 316797400, 1790860249, 1361707162, 3375567210, 1523686684
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2096312200, 2267825214, 4001356424, 828720964, 3787555350, 3066312848, 3041293826, 2498149970, 2852868026, 1755391636, 4170695914, 387990913, 245157913, 3073518436, 625510531, 2150730662
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vv_i32m1 (data1_v, data2_v, mask, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3004223180, 4557982276, 4112572589, 4020537427, 6343781375, 6508031563, 5299890024, 3408197191, 4357587271, 3604844475, 7181407584, 704788313, 2036018162, 4435225598, 4001077741, 3674417346
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
