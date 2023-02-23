/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    109, 65, 179, 183, 100, 238, 186, 162, 125, 249, 197, 151, 1, 223, 238, 127
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    184, 29, 231, 49, 234, 216, 200, 50, 219, 105, 47, 163, 246, 37, 84, 210
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    36, 255, 228, 206, 130, 5, 25, 206, 225, 106, 197, 160, 157, 19, 227, 92
    };
    int8_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8m1_t out_data = __riscv_vadd_vx_i8m1_m (mask, data1, data2, vl)
        vint8m1_t __riscv_vse8_v_i8m1 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    293, 94, 410, 206, 130, 5, 386, 206, 225, 354, 197, 314, 157, 260, 322, 337
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
