/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16mf4_t data1[] = {
    21344, 29685
    };
    const vint16mf4_t *in1 = &data1[0];
    vint16mf4_t data2[] = {
    49732, 40539
    };
    const vint16mf4_t *in2 = &data2[0];
    vint16mf4_t out_data[64];
    vint16mf4_t *out = &out_data[0];
    for (int n = 2, Q_element = 16;n >= 0; n -= Q_element) {
        vint16mf4_t out = __riscv_vadd_vv_i16mf4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16mf4_t golden[] = {
    71076, 70224
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
