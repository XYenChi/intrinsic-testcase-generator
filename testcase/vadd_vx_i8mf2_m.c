/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    1, 25, 119, 95, 161, 222, 103, 193, 81, 67, 227, 255, 233, 81, 154, 14
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    103, 223, 45, 51, 40, 94, 6, 177, 102, 150, 131, 32, 4, 232, 151, 135
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    167, 203, 116, 125, 0, 213, 83, 255, 218, 124, 176, 90, 65, 2, 212, 228
    };
    int8_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8mf2_t out_data = __riscv_vadd_vx_i8mf2_m (mask, data1, data2, vl)
        vint8mf2_t __riscv_vse8_v_i8mf2 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    167, 203, 116, 125, 201, 316, 83, 370, 218, 124, 358, 287, 237, 313, 212, 228
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
