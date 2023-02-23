/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    193, 49, 173, 94, 160, 8, 199, 98, 30, 218, 16, 14, 42, 133, 21, 32
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    92, 215, 135, 23, 246, 140, 118, 210, 11, 85, 121, 5, 200, 231, 239, 228
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    96, 139, 34, 39, 67, 221, 185, 133, 196, 83, 3, 217, 137, 160, 247, 16
    };
    int8_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8mf4_t out_data = __riscv_vadd_vx_i8mf4_m (mask, data1, data2, vl)
        vint8mf4_t __riscv_vse8_v_i8mf4 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    285, 139, 308, 39, 406, 221, 317, 308, 41, 303, 3, 217, 242, 160, 247, 260
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
