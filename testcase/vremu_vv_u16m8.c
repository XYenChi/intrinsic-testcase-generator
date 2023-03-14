/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    19, 24, 146, 203, 34, 215, 76, 1, 86, 233, 170, 150, 31, 219, 156, 128
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    171, 221, 218, 217, 57, 159, 204, 186, 82, 74, 210, 142, 227, 201, 119, 89
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m8_t data1_v = __riscv_vle16_v_u16m8 (in1, vl);
    vuint16m8_t data2_v = __riscv_vle16_v_u16m8 (in2, vl);
    vuint16m8_t out_v = __riscv_vle16_v_u16m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vremu_vv_u16m8 (data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m8 (uint16_t *out, vuint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    0, 5, 72, 14, 23, 159, 52, 0, 82, 74, 40, 142, 10, 201, 119, 89
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
