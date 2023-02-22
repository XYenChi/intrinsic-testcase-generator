/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf2_t data1[] = {
    119, 25, 79, 151, 227, 158, 132, 217
    };
    const vint8mf2_t *in1 = &data1[0];
    vint8mf2_t data2[] = {
    222, 129, 117, 92, 81, 44, 46, 176
    };
    const vint8mf2_t *in2 = &data2[0];
    vint8mf2_t out_data[64];
    vint8mf2_t *out = &out_data[0];
    for (int n = 8, Q_element = 8;n >= 0; n -= Q_element) {
        vint8mf2_t out = __riscv_vadd_vv_i8mf2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf2_t golden[] = {
    341, 154, 196, 243, 308, 202, 178, 393
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
