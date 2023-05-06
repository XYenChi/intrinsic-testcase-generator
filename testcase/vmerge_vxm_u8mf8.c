/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    213, 225, 112, 4, 14, 168, 108, 31, 89, 11, 29, 247, 34, 121, 196, 83
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    160, 12, 219, 142, 144, 58, 2, 64, 79, 255, 214, 215, 33, 146, 229, 188
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    uint64_t masked[] = {
    0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1
    };
    const uint64_t *mask = &masked[0];
    vuint8mf8_t data1_v = __riscv_vle8_v_u8mf8 (in1, vl);
    vuint8mf8_t data2_v = __riscv_vle8_v_u8mf8 (in2, vl);
    vuint8mf8_t out_v = __riscv_vle8_v_u8mf8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vxm_u8mf8 (data1_v, data2_v, masked size_t vl);
        void __riscv_vse8_v_u8mf8 (uint8_t *out, vuint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    213, 225, 219, 142, 144, 168, 108, 31, 79, 255, 214, 247, 33, 146, 196, 188
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
