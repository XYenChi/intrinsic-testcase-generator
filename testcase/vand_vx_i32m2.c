/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3330347762, 3586521702, 3400817067, 2635410321, 1183855278, 815442079, 2197634912, 3131377056, 2060542694, 3293170000, 2455318708, 1177968789, 1012642534, 2829054029, 3975694829, 3196308577
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    112518377, 714983631, 2578801320, 880006106, 3693536476, 2206523591, 3800521730, 2965346275, 3061110542, 3634391265, 3105216139, 59604672, 3357095324, 4282175853, 1178118380, 3248834925
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
    112518377, 714983631, 2578801320, 880006106, 3693536476, 2206523591, 3800521730, 2965346275, 3061110542, 3634391265, 3105216139, 59604672, 3357095324, 4282175853, 1178118380, 3248834925
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
