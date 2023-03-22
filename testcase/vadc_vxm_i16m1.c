/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    102, 6, 74, -58, -41, -57, 89, 87, 27, 98, 15, 59, 123, 73, -14, 93
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -117, -104, -99, 89, -80, 100, 106, 16, -100, 103, 126, 91, -74, -68, -39, -35
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    uint16_t masked[] = {
    1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0
    };
    const uint16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1 (in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1 (in2, vl);
    vint16m1_t out_v = __riscv_vle16_v_i16m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vxm_i16m1 (data1_v, data2_v, masked, vl);
        void __riscv_vse16_v_i16m1 (int16_t *out, vint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -14, -97, -24, 32, -120, 44, 195, 103, -72, 202, 141, 151, 50, 5, -52, 58
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
