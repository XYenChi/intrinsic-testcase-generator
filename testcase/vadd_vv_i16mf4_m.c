/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16mf4_t data1[] = {
    4745, 15811
    };
    const vint16mf4_t *in1 = &data1[0];
    vint16mf4_t data2[] = {
    47705, 56042
    };
    const vint16mf4_t *in2 = &data2[0];
    vint16mf4_t out_data[] = {
    39045, 64771
    };
    vint16mf4_t *out = &out_data[0];
    int masked[] = {
    0, 0
    };
    const int *mask = &masked[0];
    for (int n = 2, Q_element = 16;n >= 0; n -= Q_element) {
        vint16mf4_t out = __riscv_vadd_vv_i16mf4_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint16mf4_t golden[] = {
    39045, 64771
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
