/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    205, 16, 251, 218, 22, 182, 113, 127, 132, 200, 49, 175, 151, 70, 163, 240
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    101, 94, 233, 242, 200, 29, 182, 152, 14, 68, 54, 70, 108, 30, 128, 251
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    252, 212, 31, 178, 29, 187, 14, 244, 41, 94, 3, 149, 200, 45, 105, 89
    };
    int8_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8m1_t out_data = __riscv_vadd_vv_i8m1_m (mask, data1, data2, vl)
        vint8m1_t __riscv_vse8_v_i8m1 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    252, 110, 484, 178, 29, 211, 14, 244, 41, 268, 3, 245, 200, 45, 105, 89
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
