/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m1_t data1[] = {
    64168, 8494, 39472, 46890, 43737, 31501, 28603, 43854
    };
    const vint16m1_t *in1 = &data1[0];
    vint16m1_t data2[] = {
    21680, 2071, 13261, 45209, 42607, 33572, 15309, 14895
    };
    const vint16m1_t *in2 = &data2[0];
    vint16m1_t out_data[] = {
    31046, 62979, 39207, 9772, 53817, 20635, 28767, 5289
    };
    vint16m1_t *out = &out_data[0];
    int masked[] = {
    1, 0, 0, 1, 0, 0, 1, 1
    };
    const int *mask = &masked[0];
    for (int n = 8, Q_element = 16;n >= 0; n -= Q_element) {
        vint16m1_t out = __riscv_vadd_vv_i16m1_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint16m1_t golden[] = {
    85848, 62979, 39207, 92099, 53817, 20635, 43912, 58749
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
