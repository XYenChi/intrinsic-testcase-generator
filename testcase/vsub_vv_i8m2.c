/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    62, -71, -8, 27, -117, 47, 110, -99, 114, 125, -90, -61, 54, -47, 47, 82
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -61, -67, 56, 94, 64, 125, 70, -125, 36, -46, 36, 112, -51, 111, 39, -59
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m2(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2 (in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2 (in2, vl);
    vint8m2_t out_v = __riscv_vle8_v_i8m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_i8m2 (data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m2 (int8_t *out, vint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    123, -4, -64, -67, -128, -78, 40, 26, 78, 127, -126, -128, 105, -128, 8, 127
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
