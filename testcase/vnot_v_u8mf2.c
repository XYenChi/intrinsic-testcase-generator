/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    74, 21, 137, 133, 169, 139, 53, 12, 211, 66, 64, 170, 117, 140, 134, 20
    };
    const uint8_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8mf2_t data1_v = __riscv_vle8_v_u8mf2 (in1, vl);
    vuint8mf2_t out_v = __riscv_vle8_v_u8mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnot_v_u8mf2 (data1_v, vl);
        void __riscv_vse8_v_u8mf2 (uint8_t *out, vuint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    -75, -22, -138, -134, -170, -140, -54, -13, -212, -67, -65, -171, -118, -141, -135, -21
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
