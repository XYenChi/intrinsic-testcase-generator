/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    151, 152, 150, 8, 34, 49, 97, 1, 40, 47, 31, 48, 115, 116, 126, 67
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    192, 185, 50, 50, 71, 104, 27, 195, 150, 163, 110, 0, 167, 221, 11, 179
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const uint out_data[] = {
    0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1
    };
    const uint16_t *out = &out_data[0];
    uint8_t masked[] = {
    0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0
    };
    const uint8_t *mask = &masked[0];
    vuint16m2_t data1_v = __riscv_vle16_v_u16m2_m (mask, in1, vl);
    vuint16m2_t data2_v = __riscv_vle16_v_u16m2_m (mask, in2, vl);
    vuint16m2_t out_v = __riscv_vle16_v_u16m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vv_u16m2_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m2 (bool16_t mask, uint16_t *out, vuint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    0, 0, 150, 8, 65499, 0, 97, 65342, 0, 65420, 1, 1, 65484, 116, 126, 1
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
