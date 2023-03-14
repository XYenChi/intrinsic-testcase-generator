/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    106, 48, 213, 8, 225, 160, 83, 202, 229, 249, 180, 229, 61, 143, 107, 181
    };
    const uint8_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8m4_t data1_v = __riscv_vle8_v_u8m4 (in1, vl);
    vuint8m4_t out_v = __riscv_vle8_v_u8m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_8m4 (data1_v, vl);
        void __riscv_vse8_v_u8m4 (uint8_t *out, vuint8m4_t out_v, size_t vl);
        in1 += 1;
    uint8_t golden[] = {
    -106, -48, -213, -8, -225, -160, -83, -202, -229, -249, -180, -229, -61, -143, -107, -181
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
