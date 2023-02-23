/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    179, 91, 47, 68, 165, 144, 46, 204, 68, 157, 255, 247, 147, 138, 21, 234
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    238, 71, 49, 44, 226, 95, 184, 27, 120, 180, 13, 195, 140, 170, 25, 87
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    5, 103, 138, 26, 121, 23, 159, 212, 187, 85, 139, 233, 80, 103, 103, 211
    };
    int8_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8mf4_t out_data = __riscv_vadd_vv_i8mf4_m (mask, data1, data2, vl)
        vint8mf4_t __riscv_vse8_v_i8mf4 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    417, 162, 96, 26, 391, 239, 159, 212, 188, 85, 139, 442, 287, 308, 103, 321
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
