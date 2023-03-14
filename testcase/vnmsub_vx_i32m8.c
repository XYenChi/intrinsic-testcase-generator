/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    102, 53, -38, -123, 102, 13, 69, -127, -72, 113, -111, 10, 119, -87, -74, -57
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2, 113, -120, 99, 98, -125, -55, -32, 107, -51, 116, -98, -54, -81, 61, -119
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vx_i32m8 (out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    100, 53, 4294967258, 4294967173, 102, 138, 124, 4294967169, 4294967224, 164, 4294967185, 108, 173, 4294967290, 4294967222, 62
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
