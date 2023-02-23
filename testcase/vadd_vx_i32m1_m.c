/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    211, 234, 103, 77, 73, 206, 37, 188, 209, 195, 77, 125, 212, 208, 159, 127
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    192, 93, 105, 93, 248, 106, 144, 140, 222, 207, 154, 32, 17, 98, 102, 107
    };
    const int32_t *in2 = &data2[0];
    const int out_data[] = {
    38, 126, 6, 99, 202, 153, 108, 78, 79, 51, 76, 146, 137, 123, 100, 248
    };
    int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint32m1_t out_data = __riscv_vadd_vx_i32m1_m (mask, data1, data2, vl)
        vint32m1_t __riscv_vse32_v_i32m1 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    38, 327, 6, 170, 202, 153, 181, 328, 79, 51, 76, 146, 137, 123, 100, 234
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
