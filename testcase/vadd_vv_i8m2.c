/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m2_t data1[] = {
    225, 102, 148, 97, 99, 195, 159, 100, 101, 252, 218, 184, 111, 194, 67, 208, 254, 209, 28, 42, 18, 33, 125, 34, 48, 194, 167, 129, 186, 249, 66, 253, 105, 222, 152, 38, 99, 224, 170, 180, 48, 136, 180, 111, 6, 179, 69, 78, 19, 166, 6, 29, 147, 187, 104, 209, 42, 14, 237, 38, 151, 74, 78, 239
    };
    const vint8m2_t *in1 = &data1[0];
    vint8m2_t data2[] = {
    98, 91, 61, 11, 93, 203, 68, 107, 222, 233, 196, 70, 221, 28, 20, 184, 203, 106, 83, 148, 228, 191, 150, 41, 7, 208, 66, 213, 8, 78, 207, 253, 220, 154, 70, 64, 86, 88, 176, 124, 179, 71, 106, 152, 237, 209, 71, 176, 28, 105, 127, 110, 68, 142, 213, 30, 105, 63, 80, 141, 230, 188, 93, 235
    };
    const vint8m2_t *in2 = &data2[0];
    vint8m2_t out_data[64];
    vint8m2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m2_t out = __riscv_vadd_vv_i8m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m2_t golden[] = {
    323, 193, 209, 108, 192, 398, 227, 207, 323, 485, 414, 254, 332, 222, 87, 392, 457, 315, 111, 190, 246, 224, 275, 75, 55, 402, 233, 342, 194, 327, 273, 506, 325, 376, 222, 102, 185, 312, 346, 304, 227, 207, 286, 263, 243, 388, 140, 254, 47, 271, 133, 139, 215, 329, 317, 239, 147, 77, 317, 179, 381, 262, 171, 474
    };
    int fail = 0;
    for (int i = 0; i < 64; i++){
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
