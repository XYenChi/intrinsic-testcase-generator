/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    244, 100, 99, 45, 58, 204, 87, 158, 81, 178, 74, 210, 72, 48, 120, 225
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    221, 101, 46, 59, 54, 180, 84, 39, 176, 52, 18, 135, 8, 179, 137, 167
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    const uint out_data[] = {
    0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0
    };
    const uint8_t *out = &out_data[0];
    uint2_t masked[] = {
    1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1
    };
    const uint2_t *mask = &masked[0];
    vuint8m4_t data1_v = __riscv_vle8_v_u8m4_m (mask, in1, vl);
    vuint8m4_t data2_v = __riscv_vle8_v_u8m4_m (mask, in2, vl);
    vuint8m4_t out_v = __riscv_vle8_v_u8m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_u8m4 (bool8_t mask, uint8_t *out, vuint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    209, 201, 145, 0, 1, 128, 171, 197, 0, 0, 0, 0, 80, 0, 1, 136
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
