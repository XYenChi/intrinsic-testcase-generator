/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    197, 242, 48, 213, 112, 9, 100, 66, 29, 237, 14, 153, 157, 165, 240, 205
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    119, 48, 181, 43, 92, 248, 167, 82, 5, 157, 87, 61, 20, 67, 115, 149
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8m8_t data1_v = __riscv_vle8_v_u8m8 (in1, vl);
    vuint8m8_t data2_v = __riscv_vle8_v_u8m8 (in2, vl);
    vuint8m8_t out_v = __riscv_vle8_v_u8m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_u8m8 (uint8_t *out, vuint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0
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
