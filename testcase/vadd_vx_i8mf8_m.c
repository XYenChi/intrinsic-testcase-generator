/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    194, 20, 232, 123, 243, 72, 50, 101, 66, 58, 255, 244, 56, 36, 100, 39
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    28, 249, 6, 243, 170, 199, 206, 203, 214, 145, 83, 13, 151, 90, 22, 106
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    210, 246, 214, 149, 157, 13, 180, 77, 173, 135, 191, 205, 54, 154, 108, 85
    };
    int8_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8mf8_t out_data = __riscv_vadd_vx_i8mf8_m (mask, data1, data2, vl)
        vint8mf8_t __riscv_vse8_v_i8mf8 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    222, 246, 238, 149, 157, 13, 256, 304, 173, 203, 191, 205, 54, 154, 122, 145
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
