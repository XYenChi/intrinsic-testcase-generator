/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m2_t data1[] = {
    62, 217, 159, 67, 190, 154, 253, 15, 186, 8, 155, 194, 74, 240, 45, 36, 77, 178, 235, 154, 3, 223, 69, 80, 4, 69, 176, 188, 235, 123, 215, 36
    };
    const vint8m2_t *in1 = &data1[0];
    vint8m2_t data2[] = {
    239, 179, 51, 242, 44, 143, 201, 79, 9, 9, 89, 187, 57, 201, 167, 95, 221, 233, 200, 206, 73, 106, 123, 88, 209, 197, 178, 94, 137, 198, 242, 70
    };
    const vint8m2_t *in2 = &data2[0];
    vint8m2_t out_data[64];
    vint8m2_t *out = &out_data[0];
    for (int n = 32, Q_element = 8;n >= 0; n -= Q_element) {
        vint8m2_t out = __riscv_vadd_vx_i8m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m2_t golden[] = {
    301, 396, 210, 309, 234, 297, 454, 94, 195, 17, 244, 381, 131, 441, 212, 131, 298, 411, 435, 360, 76, 329, 192, 168, 213, 266, 354, 282, 372, 321, 457, 106
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
