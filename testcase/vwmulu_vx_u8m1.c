/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    70, 225, 141, 172, 69, 66, 85, 5, 110, 176, 153, 254, 0, 197, 88, 187
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    72, 61, 125, 219, 158, 163, 103, 73, 184, 151, 63, 214, 191, 29, 99, 233
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m1(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8m1_t data1_v = __riscv_vle8_v_u8m1 (in1, vl);
    vuint8m1_t data2_v = __riscv_vle8_v_u8m1 (in2, vl);
    vuint8m1_t out_v = __riscv_vle8_v_u8m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vwmulu_vx_u8m1 (out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8m1 (uint8_t *out, vuint8m1_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    176, 157, 217, 36, 150, 6, 51, 109, 16, 208, 167, 84, 0, 81, 8, 51
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
