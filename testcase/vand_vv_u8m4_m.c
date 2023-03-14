/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    61, 177, 55, 139, 57, 122, 163, 47, 168, 91, 2, 166, 202, 155, 245, 14
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    212, 241, 247, 6, 104, 234, 125, 185, 60, 185, 114, 7, 47, 76, 210, 125
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    const uint out_data[] = {
    1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0
    };
    const uint8_t *out = &out_data[0];
    uint2_t masked[] = {
    1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0
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
    212, 0, 0, 0, 1, 234, 125, 185, 60, 1, 0, 0, 1, 1, 210, 0
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
