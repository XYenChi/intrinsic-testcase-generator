/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    34, 16, 175, 91, 156, 218, 185, 246, 99, 50, 62, 121, 49, 222, 254, 169
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    233, 91, 133, 245, 164, 213, 62, 80, 60, 190, 146, 161, 10, 39, 38, 41
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    uint32_t masked[] = {
    0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1
    };
    const uint32_t *mask = &masked[0];
    vuint16mf2_t data1_v = __riscv_vle16_v_u16mf2 (in1, vl);
    vuint16mf2_t data2_v = __riscv_vle16_v_u16mf2 (in2, vl);
    vuint16mf2_t out_v = __riscv_vle16_v_u16mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16mf2 (uint16_t *out, vuint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    267, 108, 308, 336, 320, 432, 248, 326, 160, 240, 208, 283, 60, 261, 292, 211
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
