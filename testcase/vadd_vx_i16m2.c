/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m2_t data1[] = {
    6018, 21807, 38886, 22219, 4252, 11427, 13304, 30634, 15717, 57290, 43791, 47261, 49325, 46217, 557, 40104
    };
    const vint16m2_t *in1 = &data1[0];
    vint16m2_t data2[] = {
    33146, 20659, 822, 9420, 28226, 10099, 39221, 11824, 33532, 35456, 61682, 44691, 58783, 52861, 39821, 33230
    };
    const vint16m2_t *in2 = &data2[0];
    vint16m2_t out_data[64];
    vint16m2_t *out = &out_data[0];
    for (int n = 16, Q_element = 16;n >= 0; n -= Q_element) {
        vint16m2_t out = __riscv_vadd_vx_i16m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16m2_t golden[] = {
    39164, 42466, 39708, 31639, 32478, 21526, 52525, 42458, 49249, 92746, 105473, 91952, 108108, 99078, 40378, 73334
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
