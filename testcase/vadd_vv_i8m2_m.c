/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    23, 121, 237, 196, 149, 10, 42, 147, 248, 64, 201, 254, 140, 125, 205, 22
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    253, 114, 158, 205, 232, 142, 22, 168, 227, 57, 147, 240, 159, 64, 74, 130
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    68, 76, 154, 254, 31, 14, 122, 238, 187, 102, 22, 31, 199, 177, 198, 197
    };
    int8_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8m2_t out_data = __riscv_vadd_vv_i8m2_m (mask, data1, data2, vl)
        vint8m2_t __riscv_vse8_v_i8m2 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    276, 235, 395, 254, 31, 152, 122, 238, 475, 102, 22, 31, 299, 177, 198, 152
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
