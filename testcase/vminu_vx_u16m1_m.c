/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    242, 9, 130, 56, 120, 84, 63, 231, 154, 74, 244, 147, 45, 223, 3, 199
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    227, 106, 80, 12, 145, 88, 182, 19, 106, 111, 87, 227, 34, 190, 224, 64
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const uint out_data[] = {
    1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0
    };
    const uint16_t *out = &out_data[0];
    uint16_t masked[] = {
    1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1
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
    242, 106, 1, 56, 145, 88, 182, 0, 1, 111, 244, 1, 0, 1, 0, 199
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
