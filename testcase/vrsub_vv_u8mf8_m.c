/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    222, 22, 48, 137, 10, 157, 51, 154, 96, 51, 239, 113, 213, 145, 93, 254
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    38, 183, 211, 55, 110, 57, 69, 43, 8, 182, 62, 146, 106, 183, 17, 36
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    const uint out_data[] = {
    0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0
    };
    const uint8_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1
    };
    const uint64_t *mask = &masked[0];
    vuint8mf8_t data1_v = __riscv_vle8_v_u8mf8_m (mask, in1, vl);
    vuint8mf8_t data2_v = __riscv_vle8_v_u8mf8_m (mask, in2, vl);
    vuint8mf8_t out_v = __riscv_vle8_v_u8mf8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrsub_vx_u8mf8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8mf8 (bool8_t mask, uint8_t *out, vuint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    72, 161, 0, 0, 100, 156, 18, 145, 168, 131, 79, 1, 149, 0, 0, 38
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
