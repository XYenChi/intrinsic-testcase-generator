/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    94, -127, -70, 120, 46, 35, -44, -123, -80, 26, 82, -9, 38, 28, -36, -100
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -24, 23, -41, 26, -2, -124, 125, -114, -51, 15, 123, 78, 28, -97, 69, -61
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i32m1 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    94, 23, 4294967255, 120, 46, 35, 125, 4294967182, 4294967245, 26, 123, 78, 38, 28, 69, 4294967235
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
