/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    188, 96, 136, 200, 181, 72, 68, 199, 19, 95, 95, 144, 256, 2, 58, 115
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    201, 68, 218, 56, 176, 115, 59, 194, 140, 187, 25, 251, 228, 205, 127, 65
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
        out_v = __riscv_vsbc_vv_i8m1 (data1_v, data2_v, vl);
        void vint8m1_t __riscv_vse8_v_i8 (int8m1_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    -13, 28, -82, 144, 5, -43, 9, 5, -121, -92, 70, -107, 28, -203, -69, 50
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
