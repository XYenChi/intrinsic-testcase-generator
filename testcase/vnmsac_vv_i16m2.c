/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    78, 32, -59, 68, -15, 76, 55, 32, 117, -66, 106, 1, -80, -63, -34, 7
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -28, -76, 68, 23, -106, 83, -33, 27, -128, 64, -28, 32, -44, -58, 108, 124
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vv_i16m2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m2 (int16_t *out, vint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    2184, 2432, 4012, 63973, 63947, 59229, 1815, 64672, 14976, 4225, 2969, 65504, 62017, 61882, 3673, 64669
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
