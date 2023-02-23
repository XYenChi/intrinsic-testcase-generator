/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    75, 55, 133, 202, 104, 65, 207, 19, 150, 87, 10, 9, 241, 62, 234, 105
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    154, 53, 37, 52, 204, 119, 41, 107, 86, 27, 222, 53, 243, 237, 110, 242
    };
    const int16_t *in2 = &data2[0];
    const int out_data[] = {
    60, 175, 198, 110, 53, 20, 32, 253, 183, 148, 28, 132, 156, 9, 81, 4
    };
    int16_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint16mf2_t out_data = __riscv_vadd_vv_i16mf2_m (mask, data1, data2, vl)
        vint16mf2_t __riscv_vse16_v_i16mf2 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    229, 108, 170, 110, 308, 184, 248, 253, 236, 114, 28, 132, 484, 9, 81, 4
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
