/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    87, 18, 25, -23, 52, 124, 2, -23, -78, 115, -107, -32, 67, -120, 17, 2
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    41, -38, 120, -97, 11, -64, -68, -71, 99, -50, 71, 120, 48, -58, 86, 35
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m1(avl);
    const int out_data[] = {
    -4, -86, 116, 105, -63, -58, -68, -115, 7, -13, -121, 4, 10, -45, -9, 37
    };
    const int8_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1_m (mask, *in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1_m (mask, *in2, vl);
    vint8m1_t data1_v = __riscv_vle8_v_i8m1_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u8m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m1 (bool8_t mask, int8_t *out, vint8m1_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -4, -86, 116, 106, -62, -57, -67, -115, 8, -12, -121, 5, 10, -45, -9, 38
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
