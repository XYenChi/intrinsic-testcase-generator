/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m1_t data1[] = {
    24, 19, 128, 201, 15, 143, 196, 192, 251, 70, 183, 2, 111, 202, 236, 58, 13, 210, 249, 204, 183, 66, 151, 43, 115, 248, 204, 86, 201, 111, 3, 74, 127, 118, 210, 52, 11, 4, 212, 209, 246, 162, 233, 34, 83, 48, 126, 92, 190, 137, 232, 207, 99, 40, 72, 74, 207, 22, 222, 26, 141, 228, 240, 175
    };
    const vint16m1_t *in1 = &data1[0];
    vint16m1_t data2[] = {
    172, 154, 188, 132, 87, 223, 123, 197, 191, 139, 26, 21, 156, 160, 225, 114, 170, 147, 157, 246, 85, 187, 210, 189, 2, 64, 64, 204, 108, 24, 248, 232, 222, 35, 73, 200, 102, 187, 217, 229, 154, 81, 187, 186, 171, 138, 107, 101, 79, 217, 146, 131, 242, 139, 132, 154, 87, 187, 165, 26, 85, 19, 51, 126
    };
    const vint16m1_t *in2 = &data2[0];
    vint16m1_t out_data[64];
    vint16m1_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m1_t out = __riscv_vadd_vx_i16m1 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16m1_t golden[] = {
    196, 173, 316, 333, 102, 366, 319, 389, 442, 209, 209, 23, 267, 362, 461, 172, 183, 357, 406, 450, 268, 253, 361, 232, 117, 312, 268, 290, 309, 135, 251, 306, 349, 153, 283, 252, 113, 191, 429, 438, 400, 243, 420, 220, 254, 186, 233, 193, 269, 354, 378, 338, 341, 179, 204, 228, 294, 209, 387, 52, 226, 247, 291, 301
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