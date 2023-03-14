/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    226, 17, 183, 84, 220, 37, 36, 146, 78, 6, 149, 214, 71, 190, 175, 196
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    254, 58, 9, 149, 22, 163, 125, 80, 243, 245, 216, 232, 40, 1, 113, 243
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const uint out_data[] = {
    0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1
    };
    const uint16_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0
    };
    const uint8_t *mask = &masked[0];
    vuint16m2_t data1_v = __riscv_vle16_v_u16m2_m (mask, in1, vl);
    vuint16m2_t data2_v = __riscv_vle16_v_u16m2_m (mask, in2, vl);
    vuint16m2_t out_v = __riscv_vle16_v_u16m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16m2 (bool16_t mask, uint16_t *out, vuint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    226, 17, 366, 168, 220, 74, 72, 146, 156, 12, 149, 214, 71, 380, 350, 392
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
