/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    81, 26, 145, 49, 192, 214, 156, 144, 1, 87, 121, 208, 56, 152, 0, 148
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    233, 240, 141, 249, 189, 123, 142, 254, 235, 61, 84, 46, 17, 55, 198, 237
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8m4_t data1_v = __riscv_vle8_v_u8m4 (in1, vl);
    vuint8m4_t data2_v = __riscv_vle8_v_u8m4 (in2, vl);
    vuint8m4_t out_v = __riscv_vle8_v_u8m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i8m4 (data1_v, data2_v, vl);
        void __riscv_vse8_v_u8m4 (uint8_t *out, vuint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    185, 96, 221, 169, 192, 210, 136, 224, 235, 187, 180, 96, 184, 168, 0, 4
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
