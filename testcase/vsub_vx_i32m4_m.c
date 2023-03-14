/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    29, 59, -118, 127, 73, -15, -8, 54, -52, -28, -5, -74, -125, 64, 69, 14
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -127, 74, 35, 51, 1, 73, -108, 106, 61, 45, -70, -46, -67, 100, -86, 20
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int out_data[] = {
    0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0
    };
    const int32_t *out = &out_data[0];
    uint8_t masked[] = {
    0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1
    };
    const uint8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_i32m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m4 (bool32_t mask, int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    0, 4294967281, 1, 1, 0, 1, 100, 1, 4294967183, 0, 65, 0, 0, 1, 155, 4294967290
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
