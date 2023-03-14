/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    219, 158, 19, 118, 176, 220, 118, 170, 209, 56, 163, 208, 30, 163, 160, 98
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    117, 66, 19, 214, 135, 68, 75, 26, 227, 13, 173, 56, 213, 217, 154, 198
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m2(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8m2_t data1_v = __riscv_vle8_v_u8m2 (in1, vl);
    vuint8m2_t data2_v = __riscv_vle8_v_u8m2 (in2, vl);
    vuint8m2_t out_v = __riscv_vle8_v_u8m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrsub_vx_u8m2 (data1_v, data2_v, vl);
        void __riscv_vse8_v_u8m2 (uint8_t *out, vuint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    154, 164, 0, 96, 215, 104, 213, 112, 18, 213, 10, 104, 183, 54, 250, 100
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
