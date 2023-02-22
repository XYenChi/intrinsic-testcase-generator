/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m1_t data1[] = {
    5, 250, 232, 171, 70, 10, 82, 128, 246, 219, 84, 24, 67, 250, 216, 89
    };
    const vint8m1_t *in1 = &data1[0];
    vint8m1_t data2[] = {
    68, 110, 57, 78, 117, 36, 98, 228, 59, 151, 221, 68, 219, 159, 131, 155
    };
    const vint8m1_t *in2 = &data2[0];
    vint8m1_t out_data[64];
    vint8m1_t *out = &out_data[0];
    for (int n = 16, Q_element = 8;n >= 0; n -= Q_element) {
        vint8m1_t out = __riscv_vadd_vx_i8m1 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m1_t golden[] = {
    73, 360, 289, 249, 187, 46, 180, 356, 305, 370, 305, 92, 286, 409, 347, 244
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
