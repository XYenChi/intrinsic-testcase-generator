/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -74, -115, 10, 95, -31, -99, -123, -2, 26, 66, 95, 24, -44, -43, 63, 110
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    79, -71, 111, 61, -109, -78, -80, -35, -32, -22, 30, 19, 10, -69, 123, 12
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    uint16_t masked[] = {
    1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0
    };
    const uint16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1 (in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1 (in2, vl);
    vint16m1_t out_v = __riscv_vle16_v_i16m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_i16m1 (int16_t *out, vint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    79, -71, 111, 95, -109, -99, -123, -2, -32, -22, 95, 19, 10, -69, 63, 110
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
