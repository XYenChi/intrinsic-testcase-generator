/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m1_t data1[] = {
    1, 73, 128, 235, 183, 160, 50, 82, 26, 87, 8, 211, 223, 4, 240, 186, 219, 49, 183, 211, 189, 37, 55, 184, 111, 159, 210, 128, 91, 17, 105, 20, 165, 228, 174, 186, 205, 123, 113, 131, 228, 80, 233, 60, 13, 138, 27, 76, 159, 33, 149, 169, 25, 82, 76, 56, 71, 136, 155, 238, 188, 250, 127, 64
    };
    const vint8m1_t *in1 = &data1[0];
    vint8m1_t data2[] = {
    21, 86, 112, 157, 181, 119, 151, 17, 188, 182, 232, 225, 122, 24, 6, 209, 235, 91, 19, 111, 65, 50, 171, 40, 228, 53, 74, 241, 115, 79, 235, 194, 59, 110, 225, 154, 45, 184, 84, 17, 22, 102, 234, 45, 40, 200, 99, 191, 192, 100, 205, 212, 9, 35, 193, 88, 34, 249, 4, 83, 95, 26, 208, 109
    };
    const vint8m1_t *in2 = &data2[0];
    vint8m1_t out_data[64];
    vint8m1_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m1_t out = __riscv_vadd_vv_i8m1 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m1_t golden[] = {
    22, 159, 240, 392, 364, 279, 201, 99, 214, 269, 240, 436, 345, 28, 246, 395, 454, 140, 202, 322, 254, 87, 226, 224, 339, 212, 284, 369, 206, 96, 340, 214, 224, 338, 399, 340, 250, 307, 197, 148, 250, 182, 467, 105, 53, 338, 126, 267, 351, 133, 354, 381, 34, 117, 269, 144, 105, 385, 159, 321, 283, 276, 335, 173
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
