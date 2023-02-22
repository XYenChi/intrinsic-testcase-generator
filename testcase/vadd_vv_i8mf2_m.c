/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf2_t data1[] = {
    221, 191, 22, 59, 246, 225, 10, 245
    };
    const vint8mf2_t *in1 = &data1[0];
    vint8mf2_t data2[] = {
    99, 73, 248, 77, 58, 86, 50, 212
    };
    const vint8mf2_t *in2 = &data2[0];
    vint8mf2_t out_data[] = {
    171, 41, 69, 13, 92, 4, 51, 253
    };
    vint8mf2_t *out = &out_data[0];
    int masked[] = {
    0, 1, 0, 1, 0, 1, 0, 1
    };
    const int *mask = &masked[0];
    for (int n = 8, Q_element = 8;n >= 0; n -= Q_element) {
        vint8mf2_t out = __riscv_vadd_vv_i8mf2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint8mf2_t golden[] = {
    171, 264, 69, 136, 92, 311, 51, 457
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
