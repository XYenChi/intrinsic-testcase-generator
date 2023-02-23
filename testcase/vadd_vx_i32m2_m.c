/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    6, 47, 102, 199, 55, 245, 97, 124, 111, 126, 244, 184, 80, 142, 222, 147
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    19, 112, 103, 208, 200, 47, 129, 198, 158, 30, 99, 35, 77, 217, 81, 64
    };
    const int32_t *in2 = &data2[0];
    const int out_data[] = {
    161, 187, 226, 246, 185, 236, 3, 115, 232, 148, 136, 180, 55, 82, 185, 200
    };
    int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint32m2_t out_data = __riscv_vadd_vx_i32m2_m (mask, data1, data2, vl)
        vint32m2_t __riscv_vse32_v_i32m2 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    161, 187, 205, 407, 185, 236, 226, 115, 232, 148, 136, 180, 55, 82, 303, 211
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
