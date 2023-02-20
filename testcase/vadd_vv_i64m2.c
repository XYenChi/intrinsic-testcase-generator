/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m2_t data1[] = {
    77, 35, 169, 251, 14, 125, 191, 147, 52, 115, 115, 182, 182, 84, 22, 23, 144, 239, 65, 112, 70, 195, 151, 216, 226, 160, 24, 204, 238, 86, 2, 157, 165, 99, 222, 205, 188, 240, 126, 68, 81, 129, 153, 97, 226, 179, 126, 29, 53, 148, 3, 24, 155, 84, 64, 138, 215, 36, 85, 113, 10, 170, 134, 38
    };
    const vint64m2_t *in1 = &data1[0];
    vint64m2_t data2[] = {
    163, 247, 17, 123, 83, 172, 127, 91, 47, 89, 60, 252, 190, 38, 101, 96, 155, 5, 189, 230, 153, 206, 194, 208, 158, 178, 135, 27, 91, 215, 47, 110, 48, 25, 56, 42, 125, 175, 103, 45, 161, 67, 75, 130, 161, 105, 6, 0, 120, 212, 94, 218, 173, 174, 81, 61, 12, 37, 97, 117, 147, 110, 116, 121
    };
    const vint64m2_t *in2 = &data2[0];
    vint64m2_t out_data[64];
    vint64m2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint64m2_t out = __riscv_vadd_vv_i64m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint64m2_t golden[] = {
    240, 282, 186, 374, 97, 297, 318, 238, 99, 204, 175, 434, 372, 122, 123, 119, 299, 244, 254, 342, 223, 401, 345, 424, 384, 338, 159, 231, 329, 301, 49, 267, 213, 124, 278, 247, 313, 415, 229, 113, 242, 196, 228, 227, 387, 284, 132, 29, 173, 360, 97, 242, 328, 258, 145, 199, 227, 73, 182, 230, 157, 280, 250, 159
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
