/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    110, 84, 103, -120, 89, 116, -86, 34, -40, 98, 0, -32, -71, 123, -45, 32
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    10, 115, -63, -128, -24, -62, 66, 125, 97, -47, -124, -4, -115, 42, 124, 30
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    uint4_t masked[] = {
    0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1
    };
    const uint4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4 (in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4 (in2, vl);
    vint16m4_t out_v = __riscv_vle16_v_i16m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_i16m4 (int16_t *out, vint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    120, 200, 40, -247, 66, 55, -19, 160, 58, 52, -123, -35, -186, 165, 79, 63
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
