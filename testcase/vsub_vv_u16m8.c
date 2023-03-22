/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    28, 30, 54, 87, 174, 73, 176, 145, 64, 205, 89, 57, 251, 64, 124, 92
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    109, 159, 128, 202, 192, 77, 79, 32, 242, 69, 20, 82, 194, 175, 51, 174
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
        out_v = __riscv_vsub_vv_u16m8 (data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m8 (uint16_t *out, vuint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    65455, 65407, 65462, 65421, 65518, 65532, 97, 113, 65358, 136, 69, 65511, 57, 65425, 73, 65454
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
