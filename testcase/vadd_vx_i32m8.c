/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1170565920, 3606113945, 2657580961, 3740686132, 677100010, 3345179258, 1200642319, 3400196663, 3466943981, 1906571561, 2745674216, 3031739010, 3739632123, 4030471234, 1237054681, 1464661665
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2544889664, 2349206105, 3665119947, 1018559469, 2309670463, 3039713992, 1777204941, 1382298322, 3619284, 1581976802, 711458147, 3127295561, 3542437332, 3459912125, 3808797560, 4241816008
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3715455584, 5955320050, 6322700908, 4759245601, 2986770473, 6384893250, 2977847260, 4782494985, 3470563265, 3488548363, 3457132363, 6159034571, 7282069455, 7490383359, 5045852241, 5706477673
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
