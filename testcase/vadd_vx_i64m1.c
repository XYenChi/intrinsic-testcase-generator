/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m1_t data1[] = {
    9884353151451329175, 6098342163556006207
    };
    const vint64m1_t *in1 = &data1[0];
    vint64m1_t data2[] = {
    11660578466178787442, 13174644395941552930
    };
    const vint64m1_t *in2 = &data2[0];
    vint64m1_t out_data[64];
    vint64m1_t *out = &out_data[0];
    for (int n = 2, Q_element = 64;n >= 0; n -= Q_element) {
        vint64m1_t out = __riscv_vadd_vx_i64m1 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint64m1_t golden[] = {
    21544931617630116617, 19272986559497559137
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
