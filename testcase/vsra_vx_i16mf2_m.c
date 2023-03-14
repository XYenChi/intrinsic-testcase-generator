/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -40, 100, 67, 46, -98, -87, 97, 49, -7, 20, -23, 19, 117, -30, -38, -114
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    37, -107, 24, 96, -36, 7, 69, 17, -93, 82, -68, 66, 34, 24, 8, -69
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const int out_data[] = {
    1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1
    };
    const int16_t *out = &out_data[0];
    uint32_t masked[] = {
    1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0
    };
    const uint32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsra_vx_i16mf2_m (mask, data1_v, shift, vl);
        void __riscv_vse16_v_i16mf2 (bool16_t mask, int16_t *out, vint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -20, 50, 67, 46, -98, -44, 48, 24, -4, 20, -23, 19, 117, -30, -38, -57
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
