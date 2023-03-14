/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    114, -105, -22, -68, -6, -113, 106, 127, -3, 89, 85, 113, -44, 58, 34, 49
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    95, -19, 33, 87, -52, -82, 28, 70, -26, -1, -82, 117, -56, -38, -118, -23
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int out_data[] = {
    0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1
    };
    const int32_t *out = &out_data[0];
    uint32_t masked[] = {
    1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0
    };
    const uint32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i32m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (bool32_t mask, int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    10830, 1995, 0, 4294961380, 1, 9266, 2969, 1, 1, 4294967207, 0, 0, 2464, 4294965092, 4294963284, 1
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
