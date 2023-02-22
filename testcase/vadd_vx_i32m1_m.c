/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m1_t data1[] = {
    2493719204, 1009917385, 3222001325, 2769113412
    };
    const vint32m1_t *in1 = &data1[0];
    vint32m1_t data2[] = {
    1264201507, 1281604075, 406884417, 1516628620
    };
    const vint32m1_t *in2 = &data2[0];
    vint32m1_t out_data[] = {
    3216548823, 2244640902, 3619041768, 654987171
    };
    vint32m1_t *out = &out_data[0];
    int masked[] = {
    1, 0, 0, 1
    };
    const int *mask = &masked[0];
    for (int n = 4, Q_element = 32;n >= 0; n -= Q_element) {
        vint32m1_t out = __riscv_vadd_vx_i32m1_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint32m1_t golden[] = {
    3757920711, 2244640902, 3619041768, 4285742032
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
