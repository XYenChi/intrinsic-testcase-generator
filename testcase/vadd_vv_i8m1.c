/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m1_t data1[] = {
    88, 81, 153, 138, 171, 243, 103, 9, 154, 92, 82, 154, 110, 230, 228, 179, 197, 145, 52, 51, 122, 237, 3, 175, 129, 156, 56, 27, 222, 4, 95, 194, 183, 238, 226, 6, 149, 212, 27, 115, 2, 33, 254, 39, 18, 106, 160, 45, 19, 222, 121, 185, 20, 22, 51, 179, 171, 156, 61, 134, 153, 57, 252, 215
    };
    const vint8m1_t *in1 = &data1[0];
    vint8m1_t data2[] = {
    187, 107, 81, 217, 59, 132, 174, 83, 221, 79, 49, 94, 151, 31, 25, 239, 222, 134, 135, 213, 252, 92, 76, 35, 131, 155, 54, 91, 45, 37, 169, 216, 58, 103, 90, 221, 1, 33, 135, 105, 52, 132, 163, 22, 198, 35, 178, 175, 157, 247, 82, 184, 80, 113, 101, 151, 22, 53, 255, 80, 152, 44, 149, 58
    };
    const vint8m1_t *in2 = &data2[0];
    vint8m1_t out_data[64];
    vint8m1_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m1_t out = __riscv_vadd_vv_i8m1 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m1_t golden[] = {
    275, 188, 234, 355, 230, 375, 277, 92, 375, 171, 131, 248, 261, 261, 253, 418, 419, 279, 187, 264, 374, 329, 79, 210, 260, 311, 110, 118, 267, 41, 264, 410, 241, 341, 316, 227, 150, 245, 162, 220, 54, 165, 417, 61, 216, 141, 338, 220, 176, 469, 203, 369, 100, 135, 152, 330, 193, 209, 316, 214, 305, 101, 401, 273
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
