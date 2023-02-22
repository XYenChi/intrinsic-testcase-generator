/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m1_t data1[] = {
    136, 140, 181, 216, 173, 33, 220, 108, 105, 187, 240, 183, 142, 224, 126, 238
    };
    const vint8m1_t *in1 = &data1[0];
    vint8m1_t data2[] = {
    59, 14, 161, 137, 68, 124, 219, 101, 37, 165, 154, 208, 30, 159, 90, 178
    };
    const vint8m1_t *in2 = &data2[0];
    vint8m1_t out_data[64];
    vint8m1_t *out = &out_data[0];
    for (int n = 16, Q_element = 8;n >= 0; n -= Q_element) {
        vint8m1_t out = __riscv_vadd_vv_i8m1 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m1_t golden[] = {
    195, 154, 342, 353, 241, 157, 439, 209, 142, 352, 394, 391, 172, 383, 216, 416
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
