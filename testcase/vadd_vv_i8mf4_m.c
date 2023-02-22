/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf4_t data1[] = {
    43, 64, 238, 77
    };
    const vint8mf4_t *in1 = &data1[0];
    vint8mf4_t data2[] = {
    112, 185, 43, 128
    };
    const vint8mf4_t *in2 = &data2[0];
    vint8mf4_t out_data[] = {
    214, 205, 65, 71
    };
    vint8mf4_t *out = &out_data[0];
    int masked[] = {
    0, 1, 1, 1
    };
    const int *mask = &masked[0];
    for (int n = 4, Q_element = 8;n >= 0; n -= Q_element) {
        vint8mf4_t out = __riscv_vadd_vv_i8mf4_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint8mf4_t golden[] = {
    214, 249, 281, 205
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
