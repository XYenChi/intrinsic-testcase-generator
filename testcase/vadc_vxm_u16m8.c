/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    243, 188, 29, 47, 111, 122, 141, 2, 224, 245, 29, 49, 70, 204, 247, 92
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    187, 58, 147, 32, 127, 26, 100, 227, 101, 76, 188, 32, 140, 93, 90, 169
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    uint2_t masked[] = {
    0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1
    };
    const uint2_t *mask = &masked[0];
    vuint16m8_t data1_v = __riscv_vle16_v_u16m8 (in1, vl);
    vuint16m8_t data2_v = __riscv_vle16_v_u16m8 (in2, vl);
    vuint16m8_t out_v = __riscv_vle16_v_u16m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16m8 (uint16_t *out, vuint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    430, 246, 176, 80, 238, 149, 241, 230, 325, 321, 218, 82, 210, 298, 337, 262
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
