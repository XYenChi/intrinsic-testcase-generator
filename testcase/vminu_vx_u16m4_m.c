/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    53, 244, 245, 36, 212, 63, 43, 164, 19, 219, 79, 62, 106, 201, 73, 172
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    125, 173, 213, 118, 163, 157, 119, 133, 162, 118, 85, 157, 92, 151, 227, 97
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const uint out_data[] = {
    0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1
    };
    const uint16_t *out = &out_data[0];
    uint4_t masked[] = {
    1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0
    };
    const uint4_t *mask = &masked[0];
    vuint16m4_t data1_v = __riscv_vle16_v_u16m4_m (mask, in1, vl);
    vuint16m4_t data2_v = __riscv_vle16_v_u16m4_m (mask, in2, vl);
    vuint16m4_t out_v = __riscv_vle16_v_u16m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16m4 (bool16_t mask, uint16_t *out, vuint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    125, 1, 245, 118, 0, 0, 1, 0, 1, 0, 85, 1, 106, 1, 0, 1
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
