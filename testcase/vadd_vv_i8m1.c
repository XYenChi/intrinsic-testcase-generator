/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    144, 55, 43, 227, 195, 130, 16, 229, 50, 235, 64, 171, 186, 40, 164, 39
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    111, 67, 190, 244, 160, 209, 141, 200, 69, 186, 42, 60, 236, 0, 197, 99
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m1(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m1_t __riscv_vle8_v_i8m1 (const int8_t *in1, size_t vl);
    vint8m1_t __riscv_vle8_v_i8m1 (const int8_t *in2, size_t vl);
    vint8m1_t __riscv_vle8_v_i8m1 (const int8_t *out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        vint8m1_t out_data = __riscv_vadd_vv_i8m1 (const int8_t *in1, const int8_t *in2, size_t vl);
        vint8m1_t __riscv_vse8_v_i8m1 (*out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    255, 122, 233, 471, 355, 339, 157, 429, 119, 421, 106, 231, 422, 40, 361, 138
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
