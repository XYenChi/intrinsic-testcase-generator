/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m1_t data1[] = {
    193, 3, 243, 161, 118, 196, 173, 230, 206, 69, 180, 63, 59, 54, 229, 236, 110, 248, 30, 143, 37, 157, 67, 31, 35, 83, 216, 128, 140, 104, 9, 43, 99, 51, 74, 29, 222, 214, 147, 168, 99, 228, 135, 147, 16, 2, 228, 207, 13, 56, 182, 212, 76, 123, 143, 14, 93, 175, 212, 94, 107, 55, 109, 205
    };
    const vint64m1_t *in1 = &data1[0];
    vint64m1_t data2[] = {
    117, 0, 254, 162, 107, 101, 210, 79, 197, 50, 34, 11, 92, 125, 30, 221, 0, 198, 28, 6, 150, 241, 12, 192, 42, 203, 139, 159, 121, 186, 12, 47, 219, 252, 235, 215, 54, 125, 130, 107, 198, 159, 70, 76, 118, 0, 126, 198, 146, 176, 77, 10, 31, 137, 248, 213, 117, 94, 150, 154, 98, 122, 200, 107
    };
    const vint64m1_t *in2 = &data2[0];
    vint64m1_t out_data[64];
    vint64m1_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint64m1_t out = __riscv_vadd_vv_i64m1 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint64m1_t golden[] = {
    310, 3, 497, 323, 225, 297, 383, 309, 403, 119, 214, 74, 151, 179, 259, 457, 110, 446, 58, 149, 187, 398, 79, 223, 77, 286, 355, 287, 261, 290, 21, 90, 318, 303, 309, 244, 276, 339, 277, 275, 297, 387, 205, 223, 134, 2, 354, 405, 159, 232, 259, 222, 107, 260, 391, 227, 210, 269, 362, 248, 205, 177, 309, 312
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
