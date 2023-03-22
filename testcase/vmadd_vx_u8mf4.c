/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    45, 197, 22, 76, 149, 243, 56, 33, 152, 127, 60, 9, 3, 177, 184, 237
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    214, 74, 212, 30, 169, 132, 24, 33, 179, 190, 160, 209, 185, 247, 100, 151
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8mf4_t data1_v = __riscv_vle8_v_u8mf4 (in1, vl);
    vuint8mf4_t data2_v = __riscv_vle8_v_u8mf4 (in2, vl);
    vuint8mf4_t out_v = __riscv_vle8_v_u8mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmadd_vx_u8mf4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8mf4 (uint8_t *out, vuint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    3, 74, 212, 30, 62, 132, 80, 66, 75, 190, 160, 209, 185, 168, 100, 132
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
