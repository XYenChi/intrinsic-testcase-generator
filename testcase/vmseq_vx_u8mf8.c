/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    254, 13, 42, 95, 147, 142, 5, 91, 11, 113, 2, 167, 47, 83, 77, 7
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    175, 181, 105, 210, 225, 62, 175, 174, 178, 230, 25, 118, 233, 179, 33, 55
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8mf8_t data1_v = __riscv_vle8_v_u8mf8 (in1, vl);
    vuint8mf8_t data2_v = __riscv_vle8_v_u8mf8 (in2, vl);
    vuint8mf8_t out_v = __riscv_vle8_v_u8mf8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmseq_vx_8mf8_b64 (data1_v, data2_v, vl);
        void __riscv_vse8_v_u8mf8 (uint8_t *out, vuint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
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