/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    58, 4, 34, -15, 60, 29, -32, -113, 50, 111, -27, 40, 104, 65, -25, 113
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    72, -78, -118, 29, -7, 72, 41, -64, -120, -10, 45, 55, 55, -87, 55, -88
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i32m2 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    14, 2, 18, 4294967295, 53, 14, 4294967273, 4294967232, 30, 101, 4294967287, 15, 55, 43, 4294967276, 25
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
