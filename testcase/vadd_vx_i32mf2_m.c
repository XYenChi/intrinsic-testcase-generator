/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32mf2_t data1[] = {
    162836028, 1193574568
    };
    const vint32mf2_t *in1 = &data1[0];
    vint32mf2_t data2[] = {
    813349419, 1283889155
    };
    const vint32mf2_t *in2 = &data2[0];
    vint32mf2_t out_data[] = {
    3756393705, 51918117
    };
    vint32mf2_t *out = &out_data[0];
    int masked[] = {
    1, 1
    };
    const int *mask = &masked[0];
    for (int n = 2, Q_element = 32;n >= 0; n -= Q_element) {
        vint32mf2_t out = __riscv_vadd_vx_i32mf2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint32mf2_t golden[] = {
    976185447, 2477463723
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
