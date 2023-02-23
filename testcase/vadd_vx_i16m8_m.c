/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    2, 201, 107, 187, 127, 107, 57, 71, 190, 122, 245, 66, 107, 192, 144, 208
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    119, 18, 247, 215, 218, 156, 206, 124, 58, 238, 121, 239, 253, 208, 151, 128
    };
    const int16_t *in2 = &data2[0];
    const int out_data[] = {
    120, 112, 157, 155, 162, 131, 233, 180, 30, 110, 214, 165, 36, 52, 241, 4
    };
    int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint16m8_t out_data = __riscv_vadd_vx_i16m8_m (mask, data1, data2, vl)
        vint16m8_t __riscv_vse16_v_i16m8 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    120, 219, 157, 155, 162, 263, 263, 195, 248, 360, 366, 305, 36, 52, 241, 336
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
