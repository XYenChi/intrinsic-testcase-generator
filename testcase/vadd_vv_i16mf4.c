/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16mf4_t data1[] = {
    31, 16, 214, 54, 35, 145, 191, 252, 60, 1, 58, 167, 158, 17, 201, 9, 186, 229, 6, 251, 127, 17, 100, 222, 139, 169, 99, 132, 40, 198, 148, 147, 250, 232, 13, 211, 99, 19, 144, 178, 61, 92, 30, 182, 39, 248, 113, 55, 8, 222, 109, 150, 172, 162, 6, 14, 112, 51, 164, 203, 22, 206, 136, 90
    };
    const vint16mf4_t *in1 = &data1[0];
    vint16mf4_t data2[] = {
    150, 145, 156, 135, 95, 119, 26, 38, 219, 45, 83, 89, 252, 35, 21, 29, 227, 232, 17, 156, 89, 137, 162, 241, 39, 205, 222, 167, 217, 199, 74, 189, 32, 201, 178, 109, 90, 164, 188, 146, 27, 205, 34, 62, 22, 88, 205, 173, 220, 197, 85, 50, 216, 1, 176, 152, 201, 201, 145, 23, 120, 226, 189, 11
    };
    const vint16mf4_t *in2 = &data2[0];
    vint16mf4_t out_data[64];
    vint16mf4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16mf4_t out = __riscv_vadd_vv_i16mf4 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16mf4_t golden[] = {
    181, 161, 370, 189, 130, 264, 217, 290, 279, 46, 141, 256, 410, 52, 222, 38, 413, 461, 23, 407, 216, 154, 262, 463, 178, 374, 321, 299, 257, 397, 222, 336, 282, 433, 191, 320, 189, 183, 332, 324, 88, 297, 64, 244, 61, 336, 318, 228, 228, 419, 194, 200, 388, 163, 182, 166, 313, 252, 309, 226, 142, 432, 325, 101
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
