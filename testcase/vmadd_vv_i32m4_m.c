/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -4, -64, -94, -75, -27, -119, -123, 63, -22, -7, -116, 126, -10, -51, -48, 46
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3, -89, 28, 41, 18, 99, 81, 113, 86, 121, 115, 75, -78, -13, -67, -69
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int out_data[] = {
    0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1
    };
    const int32_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1
    };
    const uint8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmadd_vv_i32m4_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m4 (bool32_t mask, int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3, 4294967232, 4294967202, 4294967221, 18, 4294967276, 4294967173, 63, 86, 4294967289, 4294967295, 201, 4294967208, 4294967245, 4294967248, 4294967273
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
