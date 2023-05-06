/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    157, 97, 89, 136, 118, 145, 84, 124, 86, 183, 177, 183, 47, 119, 197, 103
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    32, 252, 206, 255, 50, 66, 39, 15, 40, 141, 96, 154, 235, 194, 247, 166
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
        void __riscv_vse8_v_u8m2 (uint8_t *out, vuint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    157, 252, 206, 255, 118, 145, 84, 124, 86, 183, 177, 183, 235, 194, 247, 166
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
