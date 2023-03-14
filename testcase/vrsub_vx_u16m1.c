/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    132, 160, 166, 174, 145, 190, 177, 214, 232, 22, 58, 41, 123, 221, 197, 208
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    173, 70, 158, 67, 129, 110, 249, 249, 216, 88, 57, 74, 198, 73, 218, 68
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m1_t data1_v = __riscv_vle16_v_u16m1 (in1, vl);
    vuint16m1_t data2_v = __riscv_vle16_v_u16m1 (in2, vl);
    vuint16m1_t out_v = __riscv_vle16_v_u16m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrsub_vx_u16m1 (data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m1 (uint16_t *out, vuint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    41, 65446, 65528, 65429, 65520, 65456, 72, 35, 65520, 66, 65535, 33, 75, 65388, 21, 65396
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
