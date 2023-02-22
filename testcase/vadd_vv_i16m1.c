/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m1_t data1[] = {
    19284, 58363, 55285, 43319, 9075, 30510, 44444, 65067
    };
    const vint16m1_t *in1 = &data1[0];
    vint16m1_t data2[] = {
    64311, 22415, 13012, 5577, 26407, 4571, 47772, 32279
    };
    const vint16m1_t *in2 = &data2[0];
    vint16m1_t out_data[64];
    vint16m1_t *out = &out_data[0];
    for (int n = 8, Q_element = 16;n >= 0; n -= Q_element) {
        vint16m1_t out = __riscv_vadd_vv_i16m1 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16m1_t golden[] = {
    83595, 80778, 68297, 48896, 35482, 35081, 92216, 97346
    };
    int fail = 0;
    for (int i = 0; i < 8; i++){
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
