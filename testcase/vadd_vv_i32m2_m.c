/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m2_t data1[] = {
    149, 127, 170, 37, 83, 203, 124, 142, 99, 61, 121, 21, 183, 162, 68, 233, 59, 129, 229, 172, 67, 82, 147, 197, 210, 128, 158, 211, 28, 255, 37, 233, 233, 158, 221, 185, 82, 80, 78, 74, 245, 39, 146, 147, 70, 142, 165, 105, 69, 91, 141, 145, 103, 112, 228, 112, 173, 139, 131, 223, 214, 41, 91, 250
    };
    const vint32m2_t *in1 = &data1[0];
    vint32m2_t data2[] = {
    90, 13, 57, 34, 226, 244, 245, 212, 81, 160, 48, 66, 19, 229, 131, 246, 164, 188, 210, 144, 34, 132, 208, 28, 189, 210, 197, 78, 128, 51, 231, 157, 151, 96, 55, 82, 254, 165, 69, 103, 51, 37, 78, 70, 32, 214, 24, 5, 107, 205, 109, 15, 53, 234, 166, 18, 209, 207, 38, 121, 135, 46, 179, 90
    };
    const vint32m2_t *in2 = &data2[0];
    vint32m2_t out_data[] = {
    4, 70, 143, 247, 224, 115, 9, 32, 119, 236, 190, 185, 138, 131, 234, 4, 107, 176, 139, 108, 162, 133, 160, 28, 118, 127, 249, 185, 73, 32, 143, 10, 102, 206, 90, 158, 149, 25, 219, 16, 0, 114, 7, 173, 225, 127, 215, 13, 37, 138, 206, 93, 187, 66, 50, 218, 95, 8, 219, 86, 32, 69, 172, 21
    };
    vint32m2_t *out = &out_data[0];
    int masked[] = {
    1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32m2_t out = __riscv_vadd_vv_i32m2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint32m2_t golden[] = {
    239, 140, 227, 71, 309, 115, 9, 32, 180, 221, 190, 87, 202, 131, 234, 479, 107, 317, 439, 108, 162, 133, 160, 225, 399, 338, 249, 185, 156, 306, 143, 10, 102, 206, 276, 267, 149, 25, 219, 16, 296, 76, 7, 173, 225, 356, 215, 13, 176, 138, 206, 160, 156, 346, 394, 218, 382, 346, 219, 344, 32, 87, 172, 340
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