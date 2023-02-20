/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m8_t data1[] = {
    150, 2, 247, 129, 113, 90, 128, 164, 105, 124, 101, 10, 253, 214, 144, 21, 77, 30, 72, 57, 149, 127, 224, 74, 190, 178, 101, 15, 28, 182, 111, 207, 192, 164, 248, 182, 13, 131, 65, 5, 201, 104, 252, 51, 143, 169, 220, 24, 103, 135, 102, 74, 166, 100, 88, 238, 45, 251, 98, 50, 224, 190, 28, 99
    };
    const vint8m8_t *in1 = &data1[0];
    vint8m8_t data2[] = {
    68, 154, 182, 87, 128, 90, 136, 223, 192, 238, 166, 183, 26, 217, 161, 9, 49, 70, 188, 35, 241, 85, 1, 234, 219, 57, 108, 133, 249, 127, 238, 236, 3, 2, 50, 129, 33, 250, 47, 144, 128, 235, 123, 118, 217, 203, 44, 89, 88, 35, 38, 99, 215, 235, 123, 64, 143, 249, 89, 225, 97, 2, 71, 217
    };
    const vint8m8_t *in2 = &data2[0];
    vint8m8_t out_data[64];
    vint8m8_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m8_t out = __riscv_vadd_vx_i8m8 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m8_t golden[] = {
    218, 156, 429, 216, 241, 180, 264, 387, 297, 362, 267, 193, 279, 431, 305, 30, 126, 100, 260, 92, 390, 212, 225, 308, 409, 235, 209, 148, 277, 309, 349, 443, 195, 166, 298, 311, 46, 381, 112, 149, 329, 339, 375, 169, 360, 372, 264, 113, 191, 170, 140, 173, 381, 335, 211, 302, 188, 500, 187, 275, 321, 192, 99, 316
    };
    int fail = 0;
    for (int i = 0; i < 64; i++)
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
