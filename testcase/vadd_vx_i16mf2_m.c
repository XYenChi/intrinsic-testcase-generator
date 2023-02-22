/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16mf2_t data1[] = {
    62555, 27854, 20389, 17935
    };
    const vint16mf2_t *in1 = &data1[0];
    vint16mf2_t data2[] = {
    57729, 54981, 25594, 1834
    };
    const vint16mf2_t *in2 = &data2[0];
    vint16mf2_t out_data[] = {
    65256, 36413, 22926, 55517
    };
    vint16mf2_t *out = &out_data[0];
    int masked[] = {
    0, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 4, Q_element = 16;n >= 0; n -= Q_element) {
        vint16mf2_t out = __riscv_vadd_vx_i16mf2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint16mf2_t golden[] = {
    65256, 82835, 22926, 55517
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
