/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    35, 217, 70, 157, 184, 146, 74, 231, 188, 68, 148, 12, 54, 164, 57, 126
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    81, 84, 169, 86, 111, 172, 151, 13, 66, 241, 8, 53, 90, 45, 15, 108
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    uint4_t masked[] = {
    1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1
    };
    const uint4_t *mask = &masked[0];
    vuint16m4_t data1_v = __riscv_vle16_v_u16m4 (in1, vl);
    vuint16m4_t data2_v = __riscv_vle16_v_u16m4 (in2, vl);
    vuint16m4_t out_v = __riscv_vle16_v_u16m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16m4 (uint16_t *out, vuint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    117, 301, 240, 243, 296, 319, 226, 244, 255, 310, 157, 66, 145, 210, 73, 235
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
