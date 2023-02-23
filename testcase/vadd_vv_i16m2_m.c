/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    106, 245, 86, 135, 133, 207, 160, 236, 114, 234, 154, 186, 98, 238, 185, 110
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    173, 175, 217, 166, 129, 78, 62, 204, 91, 86, 249, 105, 53, 191, 158, 201
    };
    const int16_t *in2 = &data2[0];
    const int out_data[] = {
    37, 87, 206, 13, 110, 17, 242, 137, 32, 212, 173, 59, 172, 155, 47, 253
    };
    int16_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint16m2_t out_data = __riscv_vadd_vv_i16m2_m (mask, data1, data2, vl)
        vint16m2_t __riscv_vse16_v_i16m2 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    279, 420, 206, 13, 262, 285, 242, 137, 32, 320, 173, 291, 151, 429, 47, 311
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
