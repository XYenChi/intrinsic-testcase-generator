/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    25, -84, -101, 84, -85, 6, -69, -27, -9, -29, 8, -38, -71, -65, 38, 12
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    106, 116, 59, -69, -84, -121, -93, -112, -15, -47, 17, 77, -127, -6, -85, -9
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsra_vv_i16mf2 (data1_v, shift, vl);
        void __riscv_vse16_v_i16mf2 (int16_t *out, vint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1
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
