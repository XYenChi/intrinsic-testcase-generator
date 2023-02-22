/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m2_t data1[] = {
    146, 254, 66, 215, 202, 194, 152, 185, 10, 6, 248, 54, 17, 129, 158, 160, 231, 110, 37, 18, 135, 190, 74, 128, 149, 227, 175, 143, 251, 47, 40, 50
    };
    const vint8m2_t *in1 = &data1[0];
    vint8m2_t data2[] = {
    130, 26, 245, 53, 178, 69, 145, 97, 30, 14, 181, 170, 0, 7, 31, 138, 243, 202, 47, 48, 209, 36, 89, 142, 116, 170, 26, 118, 211, 143, 30, 161
    };
    const vint8m2_t *in2 = &data2[0];
    vint8m2_t out_data[64];
    vint8m2_t *out = &out_data[0];
    for (int n = 32, Q_element = 8;n >= 0; n -= Q_element) {
        vint8m2_t out = __riscv_vadd_vv_i8m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m2_t golden[] = {
    276, 280, 311, 268, 380, 263, 297, 282, 40, 20, 429, 224, 17, 136, 189, 298, 474, 312, 84, 66, 344, 226, 163, 270, 265, 397, 201, 261, 462, 190, 70, 211
    };
    int fail = 0;
    for (int i = 0; i < 32; i++){
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
