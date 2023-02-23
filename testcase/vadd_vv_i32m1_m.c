/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    183, 83, 250, 112, 103, 82, 91, 210, 188, 42, 186, 214, 27, 240, 171, 126
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    34, 71, 182, 50, 127, 8, 181, 151, 217, 4, 16, 144, 209, 232, 223, 84
    };
    const int32_t *in2 = &data2[0];
    const int out_data[] = {
    18, 179, 60, 142, 189, 28, 59, 196, 132, 46, 215, 179, 70, 40, 61, 48
    };
    int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint32m1_t out_data = __riscv_vadd_vv_i32m1_m (mask, data1, data2, vl)
        vint32m1_t __riscv_vse32_v_i32m1 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    18, 179, 432, 142, 189, 90, 59, 196, 405, 46, 202, 179, 236, 40, 394, 210
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
