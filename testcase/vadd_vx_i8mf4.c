/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf4_t data1[] = {
    24, 63, 100, 138
    };
    const vint8mf4_t *in1 = &data1[0];
    vint8mf4_t data2[] = {
    250, 75, 139, 96
    };
    const vint8mf4_t *in2 = &data2[0];
    vint8mf4_t out_data[64];
    vint8mf4_t *out = &out_data[0];
    for (int n = 4, Q_element = 8;n >= 0; n -= Q_element) {
        vint8mf4_t out = __riscv_vadd_vx_i8mf4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf4_t golden[] = {
    274, 138, 239, 234
    };
    int fail = 0;
    for (int i = 0; i < 4; i++){
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
