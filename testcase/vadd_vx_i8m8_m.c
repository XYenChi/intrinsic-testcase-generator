/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    194, 203, 221, 222, 6, 183, 179, 47, 19, 100, 220, 159, 75, 246, 117, 249
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    243, 250, 6, 36, 106, 25, 119, 8, 168, 138, 42, 68, 153, 108, 53, 73
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    16, 241, 56, 52, 156, 214, 106, 75, 211, 188, 6, 107, 217, 208, 225, 69
    };
    int8_t *out = &out_data[0];
    bool1_t masked[] = {
    1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8m8_t out_data = __riscv_vadd_vx_i8m8_m (mask, data1, data2, vl)
        vint8m8_t __riscv_vse8_v_i8m8 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    437, 453, 56, 52, 112, 214, 298, 75, 187, 188, 6, 227, 228, 354, 170, 322
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
