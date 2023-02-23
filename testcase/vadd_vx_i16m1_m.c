/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    192, 110, 82, 220, 254, 9, 126, 213, 249, 216, 119, 82, 73, 193, 103, 6
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    135, 198, 175, 16, 239, 225, 22, 82, 214, 164, 212, 74, 219, 121, 85, 74
    };
    const int16_t *in2 = &data2[0];
    const int out_data[] = {
    107, 70, 239, 3, 226, 196, 205, 72, 120, 163, 188, 242, 221, 87, 15, 133
    };
    int16_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint16m1_t out_data = __riscv_vadd_vx_i16m1_m (mask, data1, data2, vl)
        vint16m1_t __riscv_vse16_v_i16m1 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    107, 308, 239, 236, 226, 196, 148, 295, 463, 380, 331, 156, 221, 314, 15, 133
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
