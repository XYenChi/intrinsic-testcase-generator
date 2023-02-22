/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m1_t data1[] = {
    210, 67, 125, 103, 145, 27, 253, 150, 246, 213, 51, 182, 26, 199, 219, 246
    };
    const vint8m1_t *in1 = &data1[0];
    vint8m1_t data2[] = {
    27, 18, 46, 148, 178, 177, 180, 89, 92, 120, 163, 96, 133, 18, 251, 165
    };
    const vint8m1_t *in2 = &data2[0];
    vint8m1_t out_data[] = {
    58, 110, 113, 210, 12, 201, 217, 116, 165, 72, 241, 121, 105, 45, 20, 230
    };
    vint8m1_t *out = &out_data[0];
    int masked[] = {
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1
    };
    const int *mask = &masked[0];
    for (int n = 16, Q_element = 8;n >= 0; n -= Q_element) {
        vint8m1_t out = __riscv_vadd_vx_i8m1_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint8m1_t golden[] = {
    237, 110, 113, 210, 12, 201, 217, 116, 338, 72, 214, 278, 159, 217, 470, 411
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
