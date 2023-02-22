/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m2_t data1[] = {
    213, 10, 238, 28, 169, 120, 78, 199, 106, 150, 3, 121, 18, 218, 151, 131, 29, 234, 164, 194, 179, 22, 101, 60, 7, 38, 256, 42, 98, 29, 90, 133
    };
    const vint8m2_t *in1 = &data1[0];
    vint8m2_t data2[] = {
    22, 190, 52, 167, 88, 247, 248, 66, 98, 167, 253, 188, 75, 220, 191, 129, 50, 53, 43, 75, 194, 249, 102, 96, 62, 78, 75, 70, 104, 157, 238, 124
    };
    const vint8m2_t *in2 = &data2[0];
    vint8m2_t out_data[] = {
    240, 116, 228, 37, 78, 113, 130, 4, 144, 144, 141, 72, 151, 35, 251, 175, 222, 49, 214, 25, 90, 219, 27, 83, 138, 195, 78, 61, 158, 23, 32, 177
    };
    vint8m2_t *out = &out_data[0];
    int masked[] = {
    0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1
    };
    const int *mask = &masked[0];
    for (int n = 32, Q_element = 8;n >= 0; n -= Q_element) {
        vint8m2_t out = __riscv_vadd_vx_i8m2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint8m2_t golden[] = {
    240, 116, 228, 195, 257, 367, 130, 4, 144, 317, 141, 309, 151, 35, 342, 260, 79, 287, 207, 269, 90, 271, 27, 83, 138, 195, 78, 61, 202, 23, 32, 257
    };
    int fail = 0;
    for (int i = 0; i < 32; i++){
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
