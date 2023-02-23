/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    91, 43, 102, 136, 130, 234, 75, 124, 169, 28, 10, 219, 211, 90, 76, 91
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    182, 60, 137, 62, 251, 166, 25, 187, 188, 241, 90, 222, 157, 123, 213, 46
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    85, 140, 89, 16, 56, 115, 255, 158, 94, 59, 188, 67, 233, 114, 13, 120
    };
    int8_t *out = &out_data[0];
    bool1_t masked[] = {
    1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8m8_t out_data = __riscv_vadd_vv_i8m8_m (mask, data1, data2, vl)
        vint8m8_t __riscv_vse8_v_i8m8 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    273, 140, 89, 16, 56, 400, 255, 158, 94, 269, 188, 441, 368, 114, 13, 137
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
