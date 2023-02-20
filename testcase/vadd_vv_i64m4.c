/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m4_t data1[] = {
    125, 14, 187, 74, 201, 140, 6, 206, 225, 11, 113, 10, 206, 120, 86, 227, 187, 63, 154, 91, 64, 23, 124, 250, 199, 185, 71, 44, 241, 110, 97, 30, 79, 136, 84, 243, 139, 185, 139, 206, 123, 148, 10, 85, 24, 228, 56, 125, 112, 249, 80, 8, 186, 178, 149, 198, 245, 75, 7, 179, 224, 30, 91, 195
    };
    const vint64m4_t *in1 = &data1[0];
    vint64m4_t data2[] = {
    199, 74, 110, 23, 178, 217, 16, 68, 88, 133, 45, 14, 112, 34, 37, 159, 224, 56, 222, 170, 120, 177, 94, 44, 160, 37, 109, 178, 219, 119, 228, 42, 160, 134, 80, 33, 17, 113, 90, 48, 82, 119, 1, 209, 4, 175, 88, 71, 121, 215, 91, 182, 85, 227, 232, 133, 84, 192, 132, 13, 198, 56, 76, 153
    };
    const vint64m4_t *in2 = &data2[0];
    vint64m4_t out_data[64];
    vint64m4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint64m4_t out = __riscv_vadd_vv_i64m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint64m4_t golden[] = {
    324, 88, 297, 97, 379, 357, 22, 274, 313, 144, 158, 24, 318, 154, 123, 386, 411, 119, 376, 261, 184, 200, 218, 294, 359, 222, 180, 222, 460, 229, 325, 72, 239, 270, 164, 276, 156, 298, 229, 254, 205, 267, 11, 294, 28, 403, 144, 196, 233, 464, 171, 190, 271, 405, 381, 331, 329, 267, 139, 192, 422, 86, 167, 348
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
