/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    232, 72, 180, 233, 53, 35, 22, 148, 211, 30, 171, 10, 120, 183, 190, 132
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    154, 174, 52, 187, 125, 249, 219, 244, 51, 62, 140, 10, 17, 228, 17, 134
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const uint out_data[] = {
    1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1
    };
    const uint16_t *out = &out_data[0];
    uint16_t masked[] = {
    1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1
    };
    const uint16_t *mask = &masked[0];
    vuint16m1_t data1_v = __riscv_vle16_v_u16m1_m (mask, in1, vl);
    vuint16m1_t data2_v = __riscv_vle16_v_u16m1_m (mask, in2, vl);
    vuint16m1_t out_v = __riscv_vle16_v_u16m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16m1 (bool16_t mask, uint16_t *out, vuint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    232, 0, 1, 0, 1, 0, 1, 244, 211, 0, 171, 10, 120, 0, 190, 134
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
