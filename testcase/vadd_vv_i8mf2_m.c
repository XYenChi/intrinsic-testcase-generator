/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    207, 85, 90, 11, 176, 173, 68, 175, 221, 120, 190, 224, 120, 89, 56, 32
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    239, 86, 25, 35, 165, 3, 247, 25, 106, 191, 60, 132, 211, 11, 87, 55
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    133, 208, 48, 80, 127, 155, 172, 15, 162, 17, 216, 96, 226, 247, 155, 100
    };
    int8_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8mf2_t out_data = __riscv_vadd_vv_i8mf2_m (mask, data1, data2, vl)
        vint8mf2_t __riscv_vse8_v_i8mf2 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    133, 208, 48, 46, 341, 176, 172, 200, 162, 17, 216, 96, 226, 247, 143, 100
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
