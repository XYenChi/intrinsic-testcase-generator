/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    96, 242, 225, 142, 53, 233, 237, 132, 194, 2, 183, 201, 47, 171, 34, 211
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    185, 40, 254, 83, 240, 91, 231, 15, 190, 25, 232, 44, 220, 67, 179, 213
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const uint out_data[] = {
    1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1
    };
    const uint16_t *out = &out_data[0];
    uint2_t masked[] = {
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1
    };
    const uint2_t *mask = &masked[0];
    vuint16m8_t data1_v = __riscv_vle16_v_u16m8_m (mask, in1, vl);
    vuint16m8_t data2_v = __riscv_vle16_v_u16m8_m (mask, in2, vl);
    vuint16m8_t out_v = __riscv_vle16_v_u16m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i16m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m8 (bool16_t mask, uint16_t *out, vuint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    17760, 9680, 57150, 11786, 12720, 21203, 54747, 0, 0, 1, 0, 8844, 10340, 1, 1, 44943
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
