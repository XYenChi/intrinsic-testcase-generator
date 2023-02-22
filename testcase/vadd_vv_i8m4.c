/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m4_t data1[] = {
    61, 89, 44, 64, 211, 223, 100, 176, 169, 105, 31, 19, 188, 146, 223, 221, 253, 88, 123, 196, 47, 10, 28, 227, 185, 81, 222, 22, 246, 227, 105, 190, 174, 80, 90, 58, 149, 204, 55, 217, 116, 199, 43, 40, 7, 162, 114, 188, 125, 69, 179, 235, 145, 118, 24, 79, 96, 200, 65, 119, 9, 227, 30, 253
    };
    const vint8m4_t *in1 = &data1[0];
    vint8m4_t data2[] = {
    255, 119, 191, 64, 35, 79, 231, 156, 126, 96, 38, 228, 151, 162, 218, 91, 164, 139, 253, 153, 111, 68, 62, 40, 61, 54, 248, 122, 218, 1, 23, 147, 9, 14, 127, 22, 196, 107, 17, 8, 101, 175, 62, 124, 177, 57, 34, 203, 51, 53, 120, 28, 37, 162, 222, 97, 101, 90, 232, 179, 4, 53, 113, 74
    };
    const vint8m4_t *in2 = &data2[0];
    vint8m4_t out_data[64];
    vint8m4_t *out = &out_data[0];
    for (int n = 64, Q_element = 8;n >= 0; n -= Q_element) {
        vint8m4_t out = __riscv_vadd_vv_i8m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m4_t golden[] = {
    316, 208, 235, 128, 246, 302, 331, 332, 295, 201, 69, 247, 339, 308, 441, 312, 417, 227, 376, 349, 158, 78, 90, 267, 246, 135, 470, 144, 464, 228, 128, 337, 183, 94, 217, 80, 345, 311, 72, 225, 217, 374, 105, 164, 184, 219, 148, 391, 176, 122, 299, 263, 182, 280, 246, 176, 197, 290, 297, 298, 13, 280, 143, 327
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
}
