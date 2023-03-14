/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    58, 191, 222, 104, 176, 90, 101, 246, 122, 112, 192, 153, 23, 79, 174, 175
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    100, 58, 220, 24, 193, 42, 227, 89, 235, 218, 36, 159, 64, 238, 66, 168
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16mf4_t data1_v = __riscv_vle16_v_u16mf4 (in1, vl);
    vuint16mf4_t data2_v = __riscv_vle16_v_u16mf4 (in2, vl);
    vuint16mf4_t out_v = __riscv_vle16_v_u16mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16mf4 (uint16_t *out, vuint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    100, 191, 222, 104, 193, 90, 227, 246, 235, 218, 192, 159, 64, 238, 174, 175
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
