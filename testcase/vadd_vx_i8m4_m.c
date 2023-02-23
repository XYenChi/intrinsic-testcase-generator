/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    98, 249, 131, 221, 85, 170, 172, 162, 93, 225, 97, 58, 97, 217, 155, 103
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    60, 59, 251, 18, 169, 231, 216, 23, 222, 159, 40, 194, 32, 172, 43, 223
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    147, 135, 156, 114, 23, 134, 171, 212, 13, 169, 73, 238, 193, 211, 114, 250
    };
    int8_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8m4_t out_data = __riscv_vadd_vx_i8m4_m (mask, data1, data2, vl)
        vint8m4_t __riscv_vse8_v_i8m4 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    147, 135, 382, 239, 254, 134, 171, 212, 315, 169, 73, 252, 129, 389, 114, 250
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
