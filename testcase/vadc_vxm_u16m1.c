/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    90, 46, 224, 118, 96, 236, 114, 106, 213, 159, 248, 14, 154, 22, 56, 22
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    138, 178, 195, 126, 218, 134, 200, 125, 56, 189, 114, 90, 157, 162, 92, 184
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    uint16_t masked[] = {
    1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0
    };
    const uint16_t *mask = &masked[0];
    vuint16m1_t data1_v = __riscv_vle16_v_u16m1 (in1, vl);
    vuint16m1_t data2_v = __riscv_vle16_v_u16m1 (in2, vl);
    vuint16m1_t out_v = __riscv_vle16_v_u16m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16m1 (uint16_t *out, vuint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    229, 224, 419, 245, 314, 370, 314, 231, 270, 348, 363, 105, 311, 184, 148, 206
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
