/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m4_t data1[] = {
    34, 50, 19, 182, 21, 166, 39, 202, 68, 55, 217, 224, 77, 11, 242, 64, 135, 193, 211, 84, 157, 225, 169, 105, 176, 26, 167, 85, 98, 209, 41, 21, 122, 54, 178, 140, 38, 9, 214, 238, 91, 171, 137, 143, 179, 33, 26, 169, 157, 117, 214, 61, 114, 235, 103, 122, 87, 98, 82, 222, 127, 231, 79, 72
    };
    const vint8m4_t *in1 = &data1[0];
    vint8m4_t data2[] = {
    253, 70, 64, 6, 133, 127, 198, 71, 193, 8, 153, 55, 1, 90, 151, 216, 211, 67, 163, 176, 209, 96, 142, 42, 114, 31, 106, 56, 195, 222, 185, 143, 68, 190, 28, 241, 100, 42, 189, 101, 28, 82, 21, 21, 140, 232, 87, 14, 7, 252, 32, 202, 69, 121, 188, 130, 204, 42, 10, 7, 104, 29, 124, 144
    };
    const vint8m4_t *in2 = &data2[0];
    vint8m4_t out_data[64];
    vint8m4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m4_t out = __riscv_vadd_vv_i8m4 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m4_t golden[] = {
    287, 120, 83, 188, 154, 293, 237, 273, 261, 63, 370, 279, 78, 101, 393, 280, 346, 260, 374, 260, 366, 321, 311, 147, 290, 57, 273, 141, 293, 431, 226, 164, 190, 244, 206, 381, 138, 51, 403, 339, 119, 253, 158, 164, 319, 265, 113, 183, 164, 369, 246, 263, 183, 356, 291, 252, 291, 140, 92, 229, 231, 260, 203, 216
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
