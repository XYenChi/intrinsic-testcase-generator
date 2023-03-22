/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    160, 223, 211, 142, 113, 128, 87, 3, 172, 179, 203, 57, 49, 200, 238, 153
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    58, 221, 205, 19, 52, 236, 4, 60, 73, 111, 76, 173, 85, 235, 14, 117
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
        out_v = __riscv_vmsgtu_vv_16mf4_b64 (data1_v, data2_v, vl);
        void __riscv_vse16_v_u16mf4 (uint16_t *out, vuint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1
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
