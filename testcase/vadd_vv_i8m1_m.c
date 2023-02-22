/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m1_t data1[] = {
    30, 224, 224, 249, 97, 21, 7, 158, 143, 125, 198, 48, 25, 122, 137, 221
    };
    const vint8m1_t *in1 = &data1[0];
    vint8m1_t data2[] = {
    41, 252, 74, 234, 76, 74, 79, 189, 152, 39, 123, 173, 128, 202, 103, 39
    };
    const vint8m1_t *in2 = &data2[0];
    vint8m1_t out_data[] = {
    155, 3, 223, 205, 77, 33, 192, 153, 20, 226, 157, 41, 234, 45, 105, 204
    };
    vint8m1_t *out = &out_data[0];
    int masked[] = {
    1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1
    };
    const int *mask = &masked[0];
    for (int n = 16, Q_element = 8;n >= 0; n -= Q_element) {
        vint8m1_t out = __riscv_vadd_vv_i8m1_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint8m1_t golden[] = {
    71, 476, 298, 483, 77, 95, 192, 153, 20, 164, 321, 41, 153, 45, 105, 260
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
