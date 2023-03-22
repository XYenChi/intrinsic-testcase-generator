/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    182, 207, 240, 57, 5, 196, 53, 242, 170, 182, 205, 243, 227, 94, 32, 6
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    171, 141, 209, 209, 137, 69, 54, 243, 162, 87, 127, 128, 126, 253, 58, 133
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8mf2_t data1_v = __riscv_vle8_v_u8mf2 (in1, vl);
    vuint8mf2_t data2_v = __riscv_vle8_v_u8mf2 (in2, vl);
    vuint8mf2_t out_v = __riscv_vle8_v_u8mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u8mf2 (data1_v, data2_v, vl);
        void __riscv_vse8_v_u8mf2 (uint8_t *out, vuint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    11, 66, 31, 104, 124, 127, 255, 255, 8, 95, 78, 115, 101, 97, 230, 129
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
