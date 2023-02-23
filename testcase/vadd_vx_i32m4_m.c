/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    183, 142, 223, 144, 120, 201, 14, 8, 64, 205, 128, 119, 57, 142, 24, 150
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    33, 86, 184, 153, 19, 192, 65, 238, 157, 99, 38, 128, 186, 43, 28, 106
    };
    const int32_t *in2 = &data2[0];
    const int out_data[] = {
    25, 167, 208, 146, 99, 169, 211, 174, 103, 231, 5, 41, 17, 153, 26, 16
    };
    int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint32m4_t out_data = __riscv_vadd_vx_i32m4_m (mask, data1, data2, vl)
        vint32m4_t __riscv_vse32_v_i32m4 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    216, 228, 208, 146, 99, 169, 211, 174, 221, 231, 166, 247, 243, 185, 52, 256
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
