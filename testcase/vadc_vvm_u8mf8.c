/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    141, 71, 179, 174, 2, 104, 63, 53, 34, 246, 14, 68, 11, 166, 152, 140
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    156, 17, 150, 252, 252, 150, 16, 245, 108, 207, 247, 1, 62, 87, 107, 200
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    uint64_t masked[] = {
    0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0
    };
    const uint64_t *mask = &masked[0];
    vuint8mf8_t data1_v = __riscv_vle8_v_u8mf8 (in1, vl);
    vuint8mf8_t data2_v = __riscv_vle8_v_u8mf8 (in2, vl);
    vuint8mf8_t out_v = __riscv_vle8_v_u8mf8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vvm_i8mf8 (data1_v, data2_v, masked, vl);
        void __riscv_vse8_v_u8mf8 (uint8_t *out, vuint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    297, 89, 329, 427, 254, 255, 79, 298, 143, 454, 262, 69, 74, 253, 260, 340
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
