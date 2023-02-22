/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m1_t data1[] = {
    10801640059305205471, 3145691116370575665
    };
    const vint64m1_t *in1 = &data1[0];
    vint64m1_t data2[] = {
    8834877944484051200, 8912083756529955456
    };
    const vint64m1_t *in2 = &data2[0];
    vint64m1_t out_data[] = {
    5267682742700087528, 14324180895953463989
    };
    vint64m1_t *out = &out_data[0];
    int masked[] = {
    0, 1
    };
    const int *mask = &masked[0];
    for (int n = 2, Q_element = 64;n >= 0; n -= Q_element) {
        vint64m1_t out = __riscv_vadd_vx_i64m1_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint64m1_t golden[] = {
    5267682742700087528, 12057774872900531121
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
