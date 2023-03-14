/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -105, 56, 34, -70, 65, 125, 9, -28, 1, -5, 86, 107, 8, -103, 29, -21
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -89, 3, 122, -23, 12, -75, 40, -93, -96, 122, -39, -97, -124, -84, -126, -106
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const int out_data[] = {
    1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1
    };
    const int16_t *out = &out_data[0];
    uint4_t masked[] = {
    1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0
    };
    const uint4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, in2, vl);
    vint16m4_t out_v = __riscv_vle16_v_i16m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_i16m4 (bool16_t mask, int16_t *out, vint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    65447, 0, 122, 65513, 12, 65461, 40, 1, 0, 122, 65497, 65439, 65412, 65452, 0, 1
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
