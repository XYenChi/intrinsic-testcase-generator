/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    171, 108, 20, 232, 98, 77, 122, 138, 132, 9, 177, 35, 186, 192, 238, 164
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    170, 160, 60, 111, 127, 173, 242, 63, 62, 48, 200, 61, 24, 223, 89, 210
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const uint out_data[] = {
    1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1
    };
    const uint16_t *out = &out_data[0];
    uint2_t masked[] = {
    0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1
    };
    const uint2_t *mask = &masked[0];
    vuint16m8_t data1_v = __riscv_vle16_v_u16m8_m (mask, in1, vl);
    vuint16m8_t data2_v = __riscv_vle16_v_u16m8_m (mask, in2, vl);
    vuint16m8_t out_v = __riscv_vle16_v_u16m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vx_u16m8_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m8 (bool16_t mask, uint16_t *out, vuint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    1, 0, 64337, 1, 0, 52215, 1, 56843, 1, 0, 30137, 63402, 1, 22720, 0, 31097
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
