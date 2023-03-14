/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    24, 19, 143, 109, 104, 0, 254, 201, 119, 206, 140, 74, 214, 139, 36, 224
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    231, 58, 52, 249, 174, 210, 29, 238, 208, 15, 244, 190, 43, 126, 83, 163
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const uint out_data[] = {
    0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0
    };
    const uint16_t *out = &out_data[0];
    uint2_t masked[] = {
    1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1
    };
    const uint2_t *mask = &masked[0];
    vuint16m8_t data1_v = __riscv_vle16_v_u16m8_m (mask, in1, vl);
    vuint16m8_t data2_v = __riscv_vle16_v_u16m8_m (mask, in2, vl);
    vuint16m8_t out_v = __riscv_vle16_v_u16m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmadd_vx_u16m8_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m8 (bool16_t mask, uint16_t *out, vuint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    231, 77, 143, 109, 104, 0, 254, 238, 208, 15, 384, 74, 43, 139, 83, 163
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
