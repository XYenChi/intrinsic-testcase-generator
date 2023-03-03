/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    6423, 4105, 36166, 42528, 20923, 35044, 32304, 18192, 61645, 53515, 22203, 39627, 47753, 29940, 25187, 26672
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    9156, 49546, 57583, 61347, 14684, 3197, 47682, 50948, 29904, 43923, 38457, 3869, 51561, 52135, 8711, 42072
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1 (*in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1 (*in2, vl);
    vint16m1_t out_v = __riscv_vle16_v_i16m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vx_i16m1 (data1_v, data2_v, mask, vl);
        void vint16m1_t __riscv_vse16_v_i16 (int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    15579, 53651, 93749, 103875, 35607, 38241, 79986, 69140, 91549, 97438, 60660, 43496, 99314, 82075, 33898, 68744
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
