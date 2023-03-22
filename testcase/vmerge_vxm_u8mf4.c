/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    183, 20, 156, 198, 29, 130, 248, 54, 104, 52, 13, 24, 42, 116, 128, 143
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    35, 56, 108, 51, 207, 123, 49, 222, 168, 4, 19, 67, 129, 241, 128, 255
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    uint32_t masked[] = {
    1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0
    };
    const uint32_t *mask = &masked[0];
    vuint8mf4_t data1_v = __riscv_vle8_v_u8mf4 (in1, vl);
    vuint8mf4_t data2_v = __riscv_vle8_v_u8mf4 (in2, vl);
    vuint8mf4_t out_v = __riscv_vle8_v_u8mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vxm_u8mf4 (data1_v, data2_v, masked size_t vl);
        void __riscv_vse8_v_u8mf4 (uint8_t *out, vuint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    35, 56, 156, 198, 29, 130, 248, 54, 168, 52, 19, 24, 42, 116, 128, 143
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
