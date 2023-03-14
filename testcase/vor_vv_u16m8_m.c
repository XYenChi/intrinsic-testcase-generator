/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    2, 22, 52, 247, 20, 85, 168, 188, 196, 210, 154, 118, 172, 7, 75, 100
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    232, 29, 11, 30, 161, 48, 200, 95, 49, 209, 13, 112, 173, 70, 170, 211
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const uint out_data[] = {
    1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0
    };
    const uint16_t *out = &out_data[0];
    uint2_t masked[] = {
    1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1
    };
    const uint2_t *mask = &masked[0];
    vuint16m8_t data1_v = __riscv_vle16_v_u16m8_m (mask, in1, vl);
    vuint16m8_t data2_v = __riscv_vle16_v_u16m8_m (mask, in2, vl);
    vuint16m8_t out_v = __riscv_vle16_v_u16m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vor_wv_16m8u_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m8 (bool16_t mask, uint16_t *out, vuint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    234, 31, 63, 255, 1, 117, 232, 255, 245, 211, 159, 118, 1, 1, 1, 247
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
