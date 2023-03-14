/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    182, 19, 231, 47, 242, 163, 199, 57, 76, 97, 40, 31, 252, 89, 60, 74
    };
    const uint8_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    const uint out_data[] = {
    0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0
    };
    const uint8_t *out = &out_data[0];
    uint2_t masked[] = {
    1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1
    };
    const uint2_t *mask = &masked[0];
    vuint8m4_t data1_v = __riscv_vle8_v_u8m4_m (mask, in1, vl);
    vuint8m4_t out_v = __riscv_vle8_v_u8m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnot_v_u8m4 (mask, data1_v, vl);
        void __riscv_vse8_v_u8m4 (bool8_t mask, uint8_t *out, vuint8m4_t out_v, size_t vl);
        in1 += 1;
    uint8_t golden[] = {
    -183, 1, 0, 0, -243, -164, 1, -58, -77, -98, -41, -32, -253, 0, 0, -75
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
