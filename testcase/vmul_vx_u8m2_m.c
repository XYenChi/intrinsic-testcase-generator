/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    164, 206, 113, 158, 187, 103, 67, 216, 64, 19, 117, 175, 26, 125, 252, 125
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    215, 158, 164, 255, 104, 251, 85, 95, 72, 74, 174, 16, 148, 125, 31, 205
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m2(avl);
    const uint out_data[] = {
    1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0
    };
    const uint8_t *out = &out_data[0];
    uint4_t masked[] = {
    1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0
    };
    const uint4_t *mask = &masked[0];
    vuint8m2_t data1_v = __riscv_vle8_v_u8m2_m (mask, in1, vl);
    vuint8m2_t data2_v = __riscv_vle8_v_u8m2_m (mask, in2, vl);
    vuint8m2_t out_v = __riscv_vle8_v_u8m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i8m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8m2 (bool8_t mask, uint8_t *out, vuint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    188, 0, 0, 98, 0, 1, 63, 40, 0, 0, 1, 240, 8, 0, 0, 0
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
