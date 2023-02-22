/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m1_t data1[] = {
    1577651135, 1375493139, 2413949723, 1478049261
    };
    const vint32m1_t *in1 = &data1[0];
    vint32m1_t data2[] = {
    1613221091, 1286496919, 3830206824, 4243494949
    };
    const vint32m1_t *in2 = &data2[0];
    vint32m1_t out_data[64];
    vint32m1_t *out = &out_data[0];
    for (int n = 4, Q_element = 32;n >= 0; n -= Q_element) {
        vint32m1_t out = __riscv_vadd_vv_i32m1 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32m1_t golden[] = {
    3190872226, 2661990058, 6244156547, 5721544210
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
