/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3604601734, 3569398478, 3600686566, 4175880672, 2199214299, 3121787380, 1238065816, 1877849968, 2458010934, 202078956, 3313970902, 1999870815, 2734953128, 3081868209, 3835111714, 2124388726
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3981181898, 3361196860, 3338168769, 1068257279, 2140464707, 561880294, 2708171126, 2733969837, 2332484389, 2969764121, 1334022615, 2231172640, 1058727914, 3166380106, 869323278, 2803019426
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
        out_v = __riscv_vadd_vv_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    7585783632, 6930595338, 6938855335, 5244137951, 4339679006, 3683667674, 3946236942, 4611819805, 4790495323, 3171843077, 4647993517, 4231043455, 3793681042, 6248248315, 4704434992, 4927408152
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
