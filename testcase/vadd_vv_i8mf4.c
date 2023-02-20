/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf4_t data1[] = {
    26, 109, 159, 183, 216, 122, 179, 71, 212, 223, 168, 62, 87, 97, 191, 41, 211, 18, 225, 52, 80, 210, 77, 56, 84, 140, 152, 149, 60, 145, 150, 89, 228, 198, 197, 204, 55, 10, 44, 78, 105, 45, 73, 108, 164, 226, 147, 241, 168, 92, 115, 148, 91, 236, 104, 146, 172, 161, 155, 54, 166, 80, 234, 160
    };
    const vint8mf4_t *in1 = &data1[0];
    vint8mf4_t data2[] = {
    131, 128, 240, 199, 250, 222, 123, 255, 102, 13, 6, 10, 196, 147, 92, 124, 57, 81, 19, 41, 113, 183, 249, 27, 40, 153, 237, 73, 62, 189, 116, 146, 248, 92, 40, 253, 192, 252, 40, 22, 52, 120, 179, 159, 24, 59, 227, 243, 8, 70, 26, 219, 71, 254, 124, 16, 78, 207, 82, 52, 155, 201, 132, 156
    };
    const vint8mf4_t *in2 = &data2[0];
    vint8mf4_t out_data[64];
    vint8mf4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf4_t out = __riscv_vadd_vv_i8mf4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf4_t golden[] = {
    157, 237, 399, 382, 466, 344, 302, 326, 314, 236, 174, 72, 283, 244, 283, 165, 268, 99, 244, 93, 193, 393, 326, 83, 124, 293, 389, 222, 122, 334, 266, 235, 476, 290, 237, 457, 247, 262, 84, 100, 157, 165, 252, 267, 188, 285, 374, 484, 176, 162, 141, 367, 162, 490, 228, 162, 250, 368, 237, 106, 321, 281, 366, 316
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
