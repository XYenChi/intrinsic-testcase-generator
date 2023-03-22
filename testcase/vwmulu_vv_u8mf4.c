/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    69, 45, 233, 4, 202, 26, 218, 224, 225, 64, 39, 157, 16, 73, 224, 48
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    181, 249, 182, 67, 124, 46, 120, 22, 73, 247, 86, 211, 85, 99, 248, 130
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
        out_v = __riscv_vwmulu_vv_u8mf4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8mf4 (uint8_t *out, vuint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    201, 197, 166, 12, 216, 172, 48, 64, 41, 192, 26, 103, 80, 59, 0, 96
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
