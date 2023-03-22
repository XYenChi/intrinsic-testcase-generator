/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -124, 52, -14, 85, 11, 45, 29, -50, 101, -52, -35, 87, -68, -101, -7, 115
    };
    const int16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    -21, -19, -128, 125, 57, -37, 67, -25, -63, 101, -47, -78, 85, 22, 123, 4
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8 (in1, vl);
    vuint16m8_t data2_v = __riscv_vle16_v_i16m8 (in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vwmaccsu_vv_i16m8 (out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m8 (int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    2605, 64549, 1792, 10625, 628, 63872, 1944, 1250, 59173, 60285, 1645, 58751, 59757, 63314, 64676, 460
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
