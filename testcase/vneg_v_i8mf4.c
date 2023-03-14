/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    29, 156, 23, 42, 18, 250, 15, 61, 111, 70, 247, 183, 49, 129, 234, 194
    };
    const uint8_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8mf4_t data1_v = __riscv_vle8_v_u8mf4 (in1, vl);
    vuint8mf4_t out_v = __riscv_vle8_v_u8mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_8mf4 (data1_v, vl);
        void __riscv_vse8_v_u8mf4 (uint8_t *out, vuint8mf4_t out_v, size_t vl);
        in1 += 1;
    uint8_t golden[] = {
    -29, -156, -23, -42, -18, -250, -15, -61, -111, -70, -247, -183, -49, -129, -234, -194
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
