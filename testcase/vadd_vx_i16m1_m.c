/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m1_t data1[] = {
    51359, 46205, 36221, 36958, 6488, 35435, 11412, 47841
    };
    const vint16m1_t *in1 = &data1[0];
    vint16m1_t data2[] = {
    57560, 12733, 16122, 49571, 54364, 58549, 5637, 2764
    };
    const vint16m1_t *in2 = &data2[0];
    vint16m1_t out_data[] = {
    60812, 46504, 17181, 38592, 42016, 58701, 39641, 14996
    };
    vint16m1_t *out = &out_data[0];
    int masked[] = {
    1, 1, 0, 1, 1, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 8, Q_element = 16;n >= 0; n -= Q_element) {
        vint16m1_t out = __riscv_vadd_vx_i16m1_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint16m1_t golden[] = {
    108919, 58938, 17181, 86529, 60852, 93984, 39641, 14996
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
