/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    106, 55, 108, -65, -68, 1, 42, -28, -122, 74, 1, 25, 9, -48, -58, 96
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    82, 83, -26, 121, -52, 23, 67, -7, -101, 78, -126, 5, 16, 109, -44, -17
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const int out_data[] = {
    0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0
    };
    const int16_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1
    };
    const uint8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vx_i16m2_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m2 (bool16_t mask, int16_t *out, vint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    106, 0, 134, 65471, 0, 65514, 42, 1, 1, 74, 0, 25, 9, 65488, 0, 96
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
