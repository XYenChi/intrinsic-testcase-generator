/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -44, 106, 127, -92, -126, 127, -24, 97, -5, -28, 36, -3, 93, -63, 77, 111
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    35, -28, -89, -91, 97, 121, -50, -99, 74, 113, -9, -98, -27, -35, -47, 22
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m1(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1 (in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1 (in2, vl);
    vint8m1_t out_v = __riscv_vle8_v_i8m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vwmacc_vv_i8m1 (out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m1 (int8_t *out, vint8m1_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    253, 105, 218, 181, 66, 7, 176, 126, 143, 164, 188, 39, 49, 158, 222, 139
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
