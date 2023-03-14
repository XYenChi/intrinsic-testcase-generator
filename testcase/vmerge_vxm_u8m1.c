/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    238, 164, 121, 201, 50, 214, 81, 250, 249, 28, 224, 220, 141, 76, 210, 109
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    126, 3, 69, 29, 138, 234, 65, 72, 116, 29, 211, 111, 36, 227, 53, 20
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m1(avl);
    uint8_t masked[] = {
    1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1
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
    126, 3, 69, 29, 138, 214, 81, 72, 249, 28, 211, 111, 36, 76, 210, 20
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
