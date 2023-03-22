/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    124, -102, -59, 82, 87, -67, -3, 92, 2, 103, -88, -121, -43, -127, -109, 41
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    100, -97, -107, -87, -20, -2, -29, -37, 15, -101, 107, -127, -92, -4, -7, -125
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    uint32_t masked[] = {
    0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0
    };
    const uint32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vvm_i16mf2 (data1_v, data2_v, masked size_t vl);
        void __riscv_vse16_v_i16mf2 (int16_t *out, vint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    124, -102, -59, 82, -20, -2, -3, 92, 2, -101, -88, -121, -43, -127, -7, 41
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
