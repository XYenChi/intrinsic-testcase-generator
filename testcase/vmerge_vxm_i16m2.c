/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    64, -75, -32, -38, -12, -31, -64, -121, -89, -2, 112, 38, 116, -63, 121, -98
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -121, 78, 121, -63, 121, 118, 48, 70, 83, -81, 86, -91, 29, 101, 114, 4
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    uint8_t masked[] = {
    0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0
    };
    const uint8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vxm_i16m2 (data1_v, data2_v, masked size_t vl);
        void __riscv_vse16_v_i16m2 (int16_t *out, vint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    64, 78, -32, -63, -12, -31, 48, -121, 83, -2, 86, -91, 116, 101, 121, -98
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
