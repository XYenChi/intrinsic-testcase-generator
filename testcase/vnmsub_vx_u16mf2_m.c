/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    227, 210, 212, 11, 138, 204, 152, 156, 164, 147, 209, 43, 19, 189, 231, 251
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    150, 121, 196, 121, 214, 47, 214, 202, 120, 122, 244, 147, 52, 169, 143, 240
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const uint out_data[] = {
    1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0
    };
    const uint16_t *out = &out_data[0];
    uint32_t masked[] = {
    0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1
    };
    const uint32_t *mask = &masked[0];
    vuint16mf2_t data1_v = __riscv_vle16_v_u16mf2_m (mask, in1, vl);
    vuint16mf2_t data2_v = __riscv_vle16_v_u16mf2_m (mask, in2, vl);
    vuint16mf2_t out_v = __riscv_vle16_v_u16mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vx_u16mf2_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16mf2 (bool16_t mask, uint16_t *out, vuint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    1, 1, 212, 0, 0, 0, 1, 1, 44, 25, 1, 43, 19, 189, 88, 251
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
