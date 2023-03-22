/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    115, 23, -32, 42, -33, 124, 79, -54, -30, 116, -120, 65, -56, -1, 6, -115
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -54, -122, 26, 98, -90, -121, 80, -80, -99, -125, -73, 114, -10, 101, -62, 125
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    uint8_t masked[] = {
    1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0
    };
    const uint8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vxm_i16m2 (data1_v, data2_v, masked, vl);
        void __riscv_vse16_v_i16m2 (int16_t *out, vint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    62, -99, -6, 140, -122, 3, 160, -133, -129, -8, -193, 179, -66, 100, -56, 10
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
