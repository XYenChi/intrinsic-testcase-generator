/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16mf2_t data1[] = {
    17647, 56555, 59778, 57710
    };
    const vint16mf2_t *in1 = &data1[0];
    vint16mf2_t data2[] = {
    50113, 58684, 6413, 54865
    };
    const vint16mf2_t *in2 = &data2[0];
    vint16mf2_t out_data[] = {
    54977, 27582, 49872, 55118
    };
    vint16mf2_t *out = &out_data[0];
    int masked[] = {
    0, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 4, Q_element = 16;n >= 0; n -= Q_element) {
        vint16mf2_t out = __riscv_vadd_vv_i16mf2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint16mf2_t golden[] = {
    54977, 115239, 49872, 55118
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
