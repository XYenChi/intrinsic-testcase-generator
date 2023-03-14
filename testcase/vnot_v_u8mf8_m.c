/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    24, 127, 212, 203, 154, 1, 244, 48, 85, 147, 223, 219, 112, 213, 193, 160
    };
    const uint8_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    const uint out_data[] = {
    0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0
    };
    const uint8_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1
    };
    const uint64_t *mask = &masked[0];
    vuint8mf8_t data1_v = __riscv_vle8_v_u8mf8_m (mask, in1, vl);
    vuint8mf8_t out_v = __riscv_vle8_v_u8mf8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnot_v_u8mf8 (mask, data1_v, vl);
        void __riscv_vse8_v_u8mf8 (bool8_t mask, uint8_t *out, vuint8mf8_t out_v, size_t vl);
        in1 += 1;
    uint8_t golden[] = {
    -25, -128, -213, 0, -155, 1, 0, 0, -86, 0, -224, -220, 1, 1, 0, -161
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
