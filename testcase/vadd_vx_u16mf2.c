/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    75, 30, 177, 124, 118, 173, 57, 23, 107, 128, 189, 99, 230, 48, 192, 187
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    101, 142, 168, 14, 66, 9, 116, 145, 158, 65, 253, 225, 230, 131, 170, 224
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16mf2_t data1_v = __riscv_vle16_v_u16mf2 (in1, vl);
    vuint16mf2_t data2_v = __riscv_vle16_v_u16mf2 (in2, vl);
    vuint16mf2_t out_v = __riscv_vle16_v_u16mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u16mf2 (data1_v, data2_v, vl);
        void __riscv_vse16_v_u16mf2 (uint16_t *out, vuint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    176, 172, 345, 138, 184, 182, 173, 168, 265, 193, 442, 324, 460, 179, 362, 411
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
