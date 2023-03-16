/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -70, 30, -65, -127, 26, -54, -122, -113, 21, 88, -105, 56, 40, -3, 33, 124
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -7, -29, 68, -121, 86, -30, -111, 7, 114, -50, -67, 118, -69, 118, 9, -52
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const int out_data[] = {
    1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1
    };
    const int16_t *out = &out_data[0];
    uint2_t masked[] = {
    0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0
    };
    const uint2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_i16m8 (bool16_t mask, int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -140, 60, -65, -254, 26, -54, -244, -226, 21, 88, -210, 56, 80, -3, 66, 124
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