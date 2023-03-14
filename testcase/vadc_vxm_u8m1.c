/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    106, 70, 152, 226, 210, 125, 157, 216, 48, 140, 227, 243, 14, 67, 252, 111
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    185, 210, 226, 213, 114, 139, 64, 98, 86, 41, 229, 147, 132, 24, 121, 99
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m1(avl);
    uint8_t masked[] = {
    1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1
    };
    const uint8_t *mask = &masked[0];
    vuint8m1_t data1_v = __riscv_vle8_v_u8m1 (in1, vl);
    vuint8m1_t data2_v = __riscv_vle8_v_u8m1 (in2, vl);
    vuint8m1_t out_v = __riscv_vle8_v_u8m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_u8m1 (uint8_t *out, vuint8m1_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    292, 280, 379, 440, 325, 264, 221, 315, 134, 182, 456, 390, 147, 92, 374, 211
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
