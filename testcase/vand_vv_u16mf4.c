/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    101, 97, 148, 200, 190, 3, 172, 239, 85, 32, 150, 91, 104, 128, 178, 96
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    194, 143, 117, 107, 171, 222, 124, 209, 85, 254, 171, 138, 222, 103, 44, 80
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16mf4_t data1_v = __riscv_vle16_v_u16mf4 (in1, vl);
    vuint16mf4_t data2_v = __riscv_vle16_v_u16mf4 (in2, vl);
    vuint16mf4_t out_v = __riscv_vle16_v_u16mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16mf4 (uint16_t *out, vuint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    194, 143, 117, 107, 171, 222, 124, 209, 85, 254, 171, 138, 222, 103, 44, 80
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
