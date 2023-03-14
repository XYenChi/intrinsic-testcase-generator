/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    255, 246, 102, 35, 4, 37, 76, 251, 73, 252, 119, 198, 104, 22, 107, 155
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    192, 59, 186, 120, 169, 96, 123, 200, 29, 93, 206, 13, 143, 224, 53, 47
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    uint16_t masked[] = {
    1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1
    };
    const uint16_t *mask = &masked[0];
    vuint8mf2_t data1_v = __riscv_vle8_v_u8mf2 (in1, vl);
    vuint8mf2_t data2_v = __riscv_vle8_v_u8mf2 (in2, vl);
    vuint8mf2_t out_v = __riscv_vle8_v_u8mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_u8mf2 (uint8_t *out, vuint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    448, 306, 288, 156, 174, 133, 199, 451, 103, 346, 325, 211, 247, 246, 160, 203
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
