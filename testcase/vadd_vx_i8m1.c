/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m1_t data1[] = {
    175, 143, 221, 161, 81, 104, 200, 205, 246, 128, 114, 164, 55, 56, 225, 73, 215, 22, 143, 251, 28, 131, 166, 175, 10, 61, 193, 2, 116, 41, 215, 81, 138, 151, 32, 210, 23, 211, 180, 203, 19, 68, 182, 126, 41, 31, 67, 119, 93, 126, 89, 150, 193, 61, 107, 210, 151, 157, 209, 87, 21, 197, 103, 235
    };
    const vint8m1_t *in1 = &data1[0];
    vint8m1_t data2[] = {
    74, 134, 33, 44, 161, 233, 92, 41, 187, 232, 204, 155, 81, 189, 119, 79, 211, 208, 58, 50, 42, 133, 1, 123, 21, 216, 102, 54, 27, 203, 66, 84, 240, 212, 197, 161, 166, 224, 4, 42, 31, 226, 193, 5, 36, 243, 27, 202, 220, 102, 183, 41, 133, 177, 192, 207, 241, 248, 21, 119, 231, 120, 115, 189
    };
    const vint8m1_t *in2 = &data2[0];
    vint8m1_t out_data[64];
    vint8m1_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m1_t out = __riscv_vadd_vx_i8m1 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m1_t golden[] = {
    249, 277, 254, 205, 242, 337, 292, 246, 433, 360, 318, 319, 136, 245, 344, 152, 426, 230, 201, 301, 70, 264, 167, 298, 31, 277, 295, 56, 143, 244, 281, 165, 378, 363, 229, 371, 189, 435, 184, 245, 50, 294, 375, 131, 77, 274, 94, 321, 313, 228, 272, 191, 326, 238, 299, 417, 392, 405, 230, 206, 252, 317, 218, 424
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
