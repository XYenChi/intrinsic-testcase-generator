/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf2_t data1[] = {
    139, 145, 115, 207, 96, 132, 121, 219
    };
    const vint8mf2_t *in1 = &data1[0];
    vint8mf2_t data2[] = {
    154, 3, 101, 94, 139, 191, 59, 197
    };
    const vint8mf2_t *in2 = &data2[0];
    vint8mf2_t out_data[] = {
    206, 216, 180, 140, 102, 246, 103, 35
    };
    vint8mf2_t *out = &out_data[0];
    int masked[] = {
    0, 1, 1, 0, 0, 0, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 8, Q_element = 8;n >= 0; n -= Q_element) {
        vint8mf2_t out = __riscv_vadd_vx_i8mf2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint8mf2_t golden[] = {
    206, 148, 216, 140, 102, 246, 103, 35
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
