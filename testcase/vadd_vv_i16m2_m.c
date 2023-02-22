/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m2_t data1[] = {
    55923, 33430, 42104, 41010, 58747, 54269, 30527, 25327, 62829, 43809, 12831, 10495, 3827, 19642, 25098, 1049
    };
    const vint16m2_t *in1 = &data1[0];
    vint16m2_t data2[] = {
    2352, 56274, 30204, 3840, 56574, 65237, 442, 26141, 36539, 34254, 7197, 13585, 46675, 12613, 36057, 17243
    };
    const vint16m2_t *in2 = &data2[0];
    vint16m2_t out_data[] = {
    29532, 9227, 4148, 48695, 50837, 47326, 44112, 18729, 33886, 17541, 44218, 471, 17459, 60541, 14349, 61703
    };
    vint16m2_t *out = &out_data[0];
    int masked[] = {
    0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1
    };
    const int *mask = &masked[0];
    for (int n = 16, Q_element = 16;n >= 0; n -= Q_element) {
        vint16m2_t out = __riscv_vadd_vv_i16m2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint16m2_t golden[] = {
    29532, 89704, 4148, 48695, 50837, 119506, 30969, 51468, 99368, 17541, 20028, 24080, 17459, 60541, 61155, 18292
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
