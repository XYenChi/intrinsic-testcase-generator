/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    131, 129, 58, 205, 85, 199, 164, 234, 93, 16, 173, 132, 72, 62, 4, 185
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    33, 17, 154, 154, 104, 31, 230, 78, 191, 177, 50, 249, 248, 162, 162, 193
    };
    const int16_t *in2 = &data2[0];
    const int out_data[] = {
    161, 89, 224, 185, 13, 59, 178, 252, 199, 250, 136, 79, 72, 129, 62, 80
    };
    int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint16m2_t out_data = __riscv_vadd_vx_i16m2_m (mask, data1, data2, vl)
        vint16m2_t __riscv_vse16_v_i16m2 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    161, 89, 212, 185, 13, 59, 394, 252, 199, 193, 136, 79, 320, 129, 62, 378
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
