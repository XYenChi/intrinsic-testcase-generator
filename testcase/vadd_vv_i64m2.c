/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m2_t data1[] = {
    16843473100393473593, 3736845343642994268, 4039181851180050175, 846227301722507468
    };
    const vint64m2_t *in1 = &data1[0];
    vint64m2_t data2[] = {
    3989993769151291884, 15064002864069504997, 2569342525425227539, 598145873198038718
    };
    const vint64m2_t *in2 = &data2[0];
    vint64m2_t out_data[64];
    vint64m2_t *out = &out_data[0];
    for (int n = 4, Q_element = 64;n >= 0; n -= Q_element) {
        vint64m2_t out = __riscv_vadd_vv_i64m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint64m2_t golden[] = {
    20833466869544765477, 18800848207712499265, 6608524376605277714, 1444373174920546186
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
