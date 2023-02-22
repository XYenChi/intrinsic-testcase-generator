/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf8_t data1[] = {
    71, 173
    };
    const vint8mf8_t *in1 = &data1[0];
    vint8mf8_t data2[] = {
    20, 80
    };
    const vint8mf8_t *in2 = &data2[0];
    vint8mf8_t out_data[64];
    vint8mf8_t *out = &out_data[0];
    for (int n = 2, Q_element = 8;n >= 0; n -= Q_element) {
        vint8mf8_t out = __riscv_vadd_vv_i8mf8 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf8_t golden[] = {
    91, 253
    };
    int fail = 0;
    for (int i = 0; i < 2; i++){
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
