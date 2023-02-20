/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf8_t data1[] = {
    235, 217, 147, 8, 189, 2, 7, 42, 41, 128, 85, 52, 103, 65, 57, 183, 169, 164, 122, 186, 179, 253, 195, 60, 185, 75, 196, 77, 135, 118, 248, 140, 199, 184, 49, 120, 88, 55, 121, 75, 86, 44, 109, 12, 231, 123, 126, 152, 254, 251, 77, 149, 109, 66, 31, 106, 147, 224, 168, 162, 134, 204, 80, 171
    };
    const vint8mf8_t *in1 = &data1[0];
    vint8mf8_t data2[] = {
    17, 18, 135, 154, 61, 80, 176, 170, 36, 34, 10, 229, 93, 14, 107, 47, 168, 150, 171, 140, 69, 204, 255, 38, 231, 167, 34, 31, 73, 82, 232, 27, 161, 227, 161, 43, 9, 157, 119, 108, 81, 81, 5, 33, 18, 219, 51, 82, 145, 38, 194, 245, 40, 190, 148, 24, 2, 216, 104, 74, 146, 192, 86, 147
    };
    const vint8mf8_t *in2 = &data2[0];
    vint8mf8_t out_data[64];
    vint8mf8_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf8_t out = __riscv_vadd_vx_i8mf8 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf8_t golden[] = {
    252, 235, 282, 162, 250, 82, 183, 212, 77, 162, 95, 281, 196, 79, 164, 230, 337, 314, 293, 326, 248, 457, 450, 98, 416, 242, 230, 108, 208, 200, 480, 167, 360, 411, 210, 163, 97, 212, 240, 183, 167, 125, 114, 45, 249, 342, 177, 234, 399, 289, 271, 394, 149, 256, 179, 130, 149, 440, 272, 236, 280, 396, 166, 318
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
