/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    87, 111, 128, 209, 176, 141, 196, 113, 36, 254, 113, 158, 163, 50, 112, 37
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    44, 193, 69, 3, 98, 67, 147, 236, 208, 6, 40, 55, 45, 211, 148, 203
    };
    const int32_t *in2 = &data2[0];
    const int out_data[] = {
    173, 11, 110, 247, 187, 226, 102, 27, 74, 136, 165, 13, 69, 120, 98, 70
    };
    int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint32m4_t out_data = __riscv_vadd_vv_i32m4_m (mask, data1, data2, vl)
        vint32m4_t __riscv_vse32_v_i32m4 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    173, 11, 110, 212, 187, 208, 102, 27, 74, 136, 165, 213, 69, 120, 260, 240
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
