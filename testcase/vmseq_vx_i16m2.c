/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -116, 102, 85, -23, -97, -48, 51, 53, 109, 124, 110, 100, -107, -57, -61, 109
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    29, 74, 41, 17, 85, 2, 10, -67, 125, 18, 72, 101, 112, -33, 81, 38
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
        out_v = __riscv_vmseq_vx_16m2_b8 (data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m2 (int16_t *out, vint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
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