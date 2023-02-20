/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m8_t data1[] = {
    71, 215, 17, 143, 153, 59, 59, 74, 183, 140, 110, 246, 172, 12, 215, 97, 34, 4, 196, 65, 210, 170, 170, 90, 31, 211, 43, 206, 124, 206, 59, 36, 234, 237, 138, 50, 77, 63, 137, 107, 76, 68, 78, 6, 14, 255, 165, 126, 5, 115, 140, 126, 121, 151, 200, 86, 76, 68, 31, 91, 68, 57, 219, 172
    };
    const vint16m8_t *in1 = &data1[0];
    vint16m8_t data2[] = {
    26, 84, 207, 39, 175, 36, 143, 11, 24, 182, 34, 58, 179, 48, 1, 42, 97, 174, 71, 16, 209, 17, 17, 210, 171, 238, 133, 150, 43, 47, 85, 192, 9, 238, 154, 54, 181, 117, 19, 53, 97, 10, 13, 8, 210, 4, 179, 118, 234, 39, 137, 132, 158, 203, 200, 48, 196, 1, 254, 67, 54, 163, 77, 115
    };
    const vint16m8_t *in2 = &data2[0];
    vint16m8_t out_data[64];
    vint16m8_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m8_t out = __riscv_vadd_vx_i16m8 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16m8_t golden[] = {
    97, 299, 224, 182, 328, 95, 202, 85, 207, 322, 144, 304, 351, 60, 216, 139, 131, 178, 267, 81, 419, 187, 187, 300, 202, 449, 176, 356, 167, 253, 144, 228, 243, 475, 292, 104, 258, 180, 156, 160, 173, 78, 91, 14, 224, 259, 344, 244, 239, 154, 277, 258, 279, 354, 400, 134, 272, 69, 285, 158, 122, 220, 296, 287
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
