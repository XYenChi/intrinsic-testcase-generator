/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32mf2_t data1[] = {
    0, 94, 137, 5, 95, 175, 102, 42, 205, 110, 16, 31, 137, 59, 141, 103, 70, 102, 169, 205, 126, 202, 0, 22, 121, 236, 110, 178, 148, 30, 170, 113, 108, 222, 199, 7, 229, 78, 124, 125, 119, 179, 35, 244, 143, 218, 213, 132, 9, 235, 66, 179, 67, 196, 99, 92, 0, 28, 177, 215, 43, 126, 83, 230
    };
    const vint32mf2_t *in1 = &data1[0];
    vint32mf2_t data2[] = {
    118, 36, 229, 105, 131, 40, 246, 129, 219, 157, 91, 17, 164, 104, 213, 17, 17, 206, 154, 26, 1, 52, 231, 104, 88, 170, 92, 47, 60, 84, 224, 232, 50, 203, 39, 30, 158, 114, 105, 147, 192, 193, 113, 133, 61, 130, 228, 212, 5, 100, 86, 203, 167, 162, 196, 247, 13, 183, 156, 32, 90, 192, 157, 219
    };
    const vint32mf2_t *in2 = &data2[0];
    vint32mf2_t out_data[64];
    vint32mf2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32mf2_t out = __riscv_vadd_vx_i32mf2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32mf2_t golden[] = {
    118, 130, 366, 110, 226, 215, 348, 171, 424, 267, 107, 48, 301, 163, 354, 120, 87, 308, 323, 231, 127, 254, 231, 126, 209, 406, 202, 225, 208, 114, 394, 345, 158, 425, 238, 37, 387, 192, 229, 272, 311, 372, 148, 377, 204, 348, 441, 344, 14, 335, 152, 382, 234, 358, 295, 339, 13, 211, 333, 247, 133, 318, 240, 449
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
