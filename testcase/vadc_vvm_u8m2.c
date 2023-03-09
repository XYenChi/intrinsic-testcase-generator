/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    74, 56, 209, 221, 110, 105, 9, 227, 144, 47, 233, 51, 143, 240, 46, 225
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    228, 203, 144, 240, 44, 153, 133, 45, 249, 207, 235, 234, 109, 48, 202, 131
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m2(avl);
    bool4_t masked[] = {
    0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vuint8m2_t data1_v = __riscv_vle8_v_u8m2 (in1, vl);
    vuint8m2_t data2_v = __riscv_vle8_v_i8m2 (in2, vl);
    vuint8m2_t out_v = __riscv_vle8_v_u8m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_u8m2 (uint8_t *out, vuint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    302, 260, 353, 462, 154, 258, 142, 273, 394, 254, 468, 286, 252, 288, 248, 357
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
