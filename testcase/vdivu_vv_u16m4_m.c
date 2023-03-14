/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    54, 199, 108, 96, 245, 244, 235, 43, 143, 103, 200, 78, 76, 6, 31, 108
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    168, 179, 51, 100, 114, 71, 183, 56, 199, 114, 94, 88, 105, 231, 14, 51
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const uint out_data[] = {
    1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0
    };
    const uint16_t *out = &out_data[0];
    uint4_t masked[] = {
    0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1
    };
    const uint4_t *mask = &masked[0];
    vuint16m4_t data1_v = __riscv_vle16_v_u16m4_m (mask, in1, vl);
    vuint16m4_t data2_v = __riscv_vle16_v_u16m4_m (mask, in2, vl);
    vuint16m4_t out_v = __riscv_vle16_v_u16m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdivu_vv_i16m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m4 (bool16_t mask, uint16_t *out, vuint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 38, 0, 0
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
