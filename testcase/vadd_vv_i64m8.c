/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m8_t data1[] = {
    40, 46, 219, 222, 198, 2, 91, 114, 9, 70, 160, 19, 228, 209, 199, 123, 117, 30, 49, 41, 239, 128, 19, 23, 87, 17, 141, 91, 0, 175, 70, 12, 28, 130, 85, 95, 87, 8, 149, 31, 138, 229, 178, 175, 89, 96, 64, 118, 20, 122, 124, 234, 251, 32, 118, 89, 39, 97, 73, 63, 8, 83, 90, 81
    };
    const vint64m8_t *in1 = &data1[0];
    vint64m8_t data2[] = {
    50, 249, 96, 55, 92, 26, 214, 154, 47, 203, 98, 218, 202, 140, 146, 45, 81, 165, 249, 133, 254, 184, 38, 62, 74, 25, 129, 4, 65, 222, 178, 111, 87, 2, 45, 67, 8, 34, 211, 162, 8, 162, 28, 59, 9, 68, 183, 254, 86, 207, 167, 64, 167, 106, 195, 13, 177, 115, 182, 179, 85, 190, 127, 206
    };
    const vint64m8_t *in2 = &data2[0];
    vint64m8_t out_data[64];
    vint64m8_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint64m8_t out = __riscv_vadd_vv_i64m8 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint64m8_t golden[] = {
    90, 295, 315, 277, 290, 28, 305, 268, 56, 273, 258, 237, 430, 349, 345, 168, 198, 195, 298, 174, 493, 312, 57, 85, 161, 42, 270, 95, 65, 397, 248, 123, 115, 132, 130, 162, 95, 42, 360, 193, 146, 391, 206, 234, 98, 164, 247, 372, 106, 329, 291, 298, 418, 138, 313, 102, 216, 212, 255, 242, 93, 273, 217, 287
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
