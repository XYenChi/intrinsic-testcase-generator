/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    195, 76, 200, 153, 85, 48, 147, 158, 176, 142, 133, 201, 94, 222, 160, 16
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    12, 248, 91, 169, 188, 148, 6, 70, 39, 55, 39, 43, 48, 120, 136, 116
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m1(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1 (*in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1 (*in2, vl);
    vint8m1_t out_v = __riscv_vle8_v_i8m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i8m1 (data1_v, data2_v, vl);
        void vint8m1_t __riscv_vse8_v_i8 (int8m1_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    2340, 18848, 18200, 25857, 15980, 7104, 882, 11060, 6864, 7810, 5187, 8643, 4512, 26640, 21760, 1856
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
