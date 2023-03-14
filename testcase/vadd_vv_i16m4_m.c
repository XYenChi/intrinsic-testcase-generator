/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -51, 91, -108, -9, -17, -108, 31, -42, 77, 5, 8, -33, 50, -112, -85, 105
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -39, 26, -110, 40, 27, -40, 35, -119, 127, -118, 26, -11, -112, -108, 126, 70
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const int out_data[] = {
    0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1
    };
    const int16_t *out = &out_data[0];
    uint4_t masked[] = {
    0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0
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
    0, 117, 65318, 1, 10, 65388, 1, 0, 0, 65423, 34, 1, 0, 1, 0, 1
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
