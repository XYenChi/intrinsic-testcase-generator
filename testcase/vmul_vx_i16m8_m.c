/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -83, 53, 114, -83, -99, 32, 0, -32, 63, -57, 77, 55, -93, -12, 109, 104
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -12, -110, 99, 11, -16, 12, -29, 68, 90, -6, 86, 77, 74, 7, -53, -19
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const int out_data[] = {
    1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1
    };
    const int16_t *out = &out_data[0];
    uint2_t masked[] = {
    0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0
    };
    const uint2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i16m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m8 (bool16_t mask, int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    1, 1, 11286, 64623, 1584, 1, 0, 63360, 1, 342, 6622, 0, 0, 0, 1, 1
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
