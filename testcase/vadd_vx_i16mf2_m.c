/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    119, 194, 171, 141, 110, 65, 151, 68, 132, 244, 205, 65, 232, 67, 169, 145
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    244, 65, 86, 63, 208, 114, 175, 218, 159, 181, 229, 220, 19, 155, 81, 139
    };
    const int16_t *in2 = &data2[0];
    const int out_data[] = {
    247, 74, 180, 123, 183, 243, 175, 125, 155, 75, 11, 48, 12, 96, 158, 148
    };
    int16_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint16mf2_t out_data = __riscv_vadd_vx_i16mf2_m (mask, data1, data2, vl)
        vint16mf2_t __riscv_vse16_v_i16mf2 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    363, 259, 257, 123, 183, 243, 326, 286, 291, 75, 434, 285, 251, 96, 158, 284
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
