/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m1_t data1[] = {
    10986, 2788, 61327, 40856, 45251, 39015, 56184, 50533
    };
    const vint16m1_t *in1 = &data1[0];
    vint16m1_t data2[] = {
    43841, 40464, 48260, 14882, 39383, 256, 27522, 34994
    };
    const vint16m1_t *in2 = &data2[0];
    vint16m1_t out_data[64];
    vint16m1_t *out = &out_data[0];
    for (int n = 8, Q_element = 16;n >= 0; n -= Q_element) {
        vint16m1_t out = __riscv_vadd_vx_i16m1 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16m1_t golden[] = {
    54827, 43252, 109587, 55738, 84634, 39271, 83706, 85527
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
