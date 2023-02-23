/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    250, 3, 75, 142, 197, 20, 87, 136, 146, 56, 9, 245, 41, 150, 95, 248
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    241, 167, 217, 220, 128, 245, 254, 47, 15, 220, 251, 88, 231, 195, 17, 119
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    90, 30, 84, 127, 30, 79, 108, 42, 6, 175, 177, 43, 152, 168, 165, 179
    };
    int8_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8m4_t out_data = __riscv_vadd_vv_i8m4_m (mask, data1, data2, vl)
        vint8m4_t __riscv_vse8_v_i8m4 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    90, 30, 292, 127, 30, 265, 341, 183, 6, 175, 260, 333, 272, 168, 112, 179
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
