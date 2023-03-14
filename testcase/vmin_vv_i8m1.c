/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    103, -21, -98, 120, -93, -116, -31, -94, -87, -20, -50, 114, 75, -59, -12, -20
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    55, 21, -46, -101, -29, 15, 72, 13, -113, 71, 50, -77, 14, -4, -59, -89
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
        out_v = __riscv_vmin_vv_i8m1 (data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m1 (int8_t *out, vint8m1_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    103, 21, 210, 120, 227, 15, 72, 13, 169, 71, 50, 114, 75, 252, 244, 236
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
