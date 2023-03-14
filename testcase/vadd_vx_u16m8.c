/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    160, 45, 0, 73, 51, 90, 115, 229, 168, 22, 209, 156, 117, 212, 62, 135
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    12, 243, 118, 36, 0, 210, 134, 0, 204, 62, 231, 0, 108, 12, 195, 97
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m8_t data1_v = __riscv_vle16_v_u16m8 (in1, vl);
    vuint16m8_t data2_v = __riscv_vle16_v_u16m8 (in2, vl);
    vuint16m8_t out_v = __riscv_vle16_v_u16m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u16m8 (data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m8 (uint16_t *out, vuint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    172, 288, 118, 109, 51, 300, 249, 229, 372, 84, 440, 156, 225, 224, 257, 232
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
