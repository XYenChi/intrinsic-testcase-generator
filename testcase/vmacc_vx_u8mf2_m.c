/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    69, 16, 62, 223, 223, 24, 29, 108, 53, 65, 53, 231, 86, 129, 162, 211
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    183, 22, 235, 36, 255, 77, 152, 175, 182, 39, 49, 175, 0, 126, 56, 67
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    const uint out_data[] = {
    1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0
    };
    const uint8_t *out = &out_data[0];
    uint16_t masked[] = {
    0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1
    };
    const uint16_t *mask = &masked[0];
    vuint8mf2_t data1_v = __riscv_vle8_v_u8mf2_m (mask, in1, vl);
    vuint8mf2_t data2_v = __riscv_vle8_v_u8mf2_m (mask, in2, vl);
    vuint8mf2_t out_v = __riscv_vle8_v_u8mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_u8mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8mf2 (bool8_t mask, uint8_t *out, vuint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    1, 97, 1, 1, 33, 56, 0, 212, 1, 231, 37, 1, 1, 126, 0, 57
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
