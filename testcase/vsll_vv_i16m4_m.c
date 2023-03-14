/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -31, -95, -122, 51, 80, -16, -77, 6, 69, 36, -110, -105, 23, 14, 109, -86
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    108, 93, -7, 9, -104, -125, -19, -3, -2, 1, 63, 72, 33, 29, 109, -102
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const int out_data[] = {
    1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0
    };
    const int16_t *out = &out_data[0];
    uint4_t masked[] = {
    1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1
    };
    const uint4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, in2, vl);
    vint16m4_t out_v = __riscv_vle16_v_i16m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_i16m4 (bool16_t mask, int16_t *out, vint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -31, -190, -244, 102, 80, -32, -154, 12, 69, 72, -220, -105, 46, 28, 218, -86
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
