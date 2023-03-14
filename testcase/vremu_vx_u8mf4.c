/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    47, 206, 66, 241, 207, 67, 165, 48, 111, 153, 254, 54, 55, 84, 221, 123
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    26, 100, 192, 141, 199, 169, 255, 236, 117, 239, 0, 132, 84, 172, 110, 96
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
        out_v = __riscv_vremu_vx_u8mf4 (data1_v, data2_v, vl);
        void __riscv_vse8_v_u8mf4 (uint8_t *out, vuint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    26, 100, 60, 141, 199, 35, 90, 44, 6, 86, 0, 24, 29, 4, 110, 96
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
