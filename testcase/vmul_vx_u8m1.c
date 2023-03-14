/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    108, 37, 87, 156, 166, 255, 243, 16, 242, 82, 19, 145, 190, 190, 120, 129
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    179, 64, 142, 38, 80, 135, 101, 111, 69, 218, 152, 62, 234, 166, 244, 237
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m1(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8m1_t data1_v = __riscv_vle8_v_u8m1 (in1, vl);
    vuint8m1_t data2_v = __riscv_vle8_v_u8m1 (in2, vl);
    vuint8m1_t out_v = __riscv_vle8_v_u8m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i8m1 (data1_v, data2_v, vl);
        void __riscv_vse8_v_u8m1 (uint8_t *out, vuint8m1_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    132, 64, 66, 40, 224, 121, 223, 240, 58, 212, 72, 30, 172, 52, 96, 109
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
