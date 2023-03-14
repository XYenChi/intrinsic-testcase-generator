/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    29, 66, 25, 237, 190, 83, 199, 237, 143, 136, 35, 198, 55, 49, 249, 135
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    184, 212, 62, 26, 22, 247, 88, 71, 158, 127, 193, 181, 8, 127, 103, 100
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    uint1_t masked[] = {
    0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0
    };
    const uint1_t *mask = &masked[0];
    vuint8m8_t data1_v = __riscv_vle8_v_u8m8 (in1, vl);
    vuint8m8_t data2_v = __riscv_vle8_v_u8m8 (in2, vl);
    vuint8m8_t out_v = __riscv_vle8_v_u8m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_u8m8 (uint8_t *out, vuint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    29, 66, 25, 26, 22, 83, 199, 71, 158, 136, 193, 198, 55, 127, 249, 135
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
