/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m2_t data1[] = {
    9098, 48380, 48098, 61218, 55237, 38419, 52304, 38768, 55898, 47012, 4895, 51359, 2447, 61678, 2145, 53826
    };
    const vint16m2_t *in1 = &data1[0];
    vint16m2_t data2[] = {
    8761, 59250, 33879, 1383, 13437, 60484, 65046, 42868, 56219, 60492, 32502, 26197, 38463, 31931, 46339, 22040
    };
    const vint16m2_t *in2 = &data2[0];
    vint16m2_t out_data[] = {
    26993, 34249, 23065, 52448, 18390, 1633, 32086, 45934, 64417, 31418, 62630, 46299, 62418, 3190, 64040, 54817
    };
    vint16m2_t *out = &out_data[0];
    int masked[] = {
    0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0
    };
    const int *mask = &masked[0];
    for (int n = 16, Q_element = 16;n >= 0; n -= Q_element) {
        vint16m2_t out = __riscv_vadd_vx_i16m2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint16m2_t golden[] = {
    26993, 34249, 23065, 52448, 18390, 98903, 32086, 81636, 64417, 31418, 62630, 46299, 62418, 3190, 48484, 54817
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
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
