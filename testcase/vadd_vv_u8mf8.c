/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    169, 132, 180, 254, 188, 139, 250, 64, 60, 53, 157, 89, 211, 187, 24, 213
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    14, 127, 55, 207, 51, 167, 64, 185, 130, 213, 197, 120, 19, 157, 248, 102
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8mf8_t data1_v = __riscv_vle8_v_u8mf8 (in1, vl);
    vuint8mf8_t data2_v = __riscv_vle8_v_u8mf8 (in2, vl);
    vuint8mf8_t out_v = __riscv_vle8_v_u8mf8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u8mf8 (data1_v, data2_v, vl);
        void __riscv_vse8_v_u8mf8 (uint8_t *out, vuint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    183, 3, 235, 205, 239, 50, 58, 249, 190, 10, 98, 209, 230, 88, 16, 59
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
