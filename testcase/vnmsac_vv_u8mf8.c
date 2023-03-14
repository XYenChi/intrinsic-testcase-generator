/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    56, 244, 106, 188, 74, 137, 88, 232, 215, 242, 17, 85, 246, 252, 124, 132
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    34, 151, 227, 4, 249, 56, 174, 59, 227, 13, 197, 122, 47, 6, 137, 132
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
        out_v = __riscv_vnmsac_vv_u8mf8 (out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8mf8 (uint8_t *out, vuint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    144, 21, 3, 16, 7, 9, 48, 137, 91, 183, 236, 127, 214, 25, 164, 240
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
