/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m4_t data1[] = {
    179, 239, 93, 39, 15, 140, 85, 185, 5, 145, 184, 209, 194, 67, 30, 137, 89, 190, 250, 84, 61, 62, 45, 213, 209, 102, 54, 211, 23, 238, 123, 10, 153, 104, 65, 66, 187, 223, 92, 194, 196, 61, 79, 96, 25, 226, 63, 84, 13, 117, 98, 248, 25, 107, 12, 180, 153, 252, 45, 194, 173, 159, 35, 249
    };
    const vint16m4_t *in1 = &data1[0];
    vint16m4_t data2[] = {
    89, 215, 4, 208, 242, 8, 79, 210, 172, 200, 211, 5, 104, 253, 170, 234, 14, 170, 227, 127, 100, 55, 196, 151, 118, 71, 29, 132, 27, 159, 207, 178, 56, 75, 51, 51, 191, 2, 162, 164, 85, 27, 192, 194, 213, 150, 211, 221, 252, 142, 223, 227, 55, 141, 130, 249, 172, 206, 49, 188, 172, 40, 129, 210
    };
    const vint16m4_t *in2 = &data2[0];
    vint16m4_t out_data[] = {
    125, 101, 203, 135, 175, 45, 155, 72, 144, 70, 181, 72, 87, 100, 235, 131, 111, 120, 142, 87, 246, 73, 179, 58, 127, 49, 119, 89, 58, 48, 1, 170, 117, 95, 144, 185, 214, 117, 255, 242, 137, 254, 94, 173, 163, 97, 196, 205, 172, 6, 119, 35, 238, 51, 24, 4, 100, 244, 178, 141, 84, 158, 40, 154
    };
    vint16m4_t *out = &out_data[0];
    int masked[] = {
    0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m4_t out = __riscv_vadd_vv_i16m4_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint16m4_t golden[] = {
    125, 454, 203, 247, 175, 45, 164, 72, 144, 70, 395, 214, 298, 100, 200, 371, 103, 120, 142, 87, 161, 73, 179, 58, 327, 49, 83, 343, 58, 397, 1, 170, 117, 95, 144, 185, 214, 117, 254, 358, 281, 88, 94, 290, 163, 376, 274, 305, 265, 259, 321, 475, 80, 248, 24, 4, 100, 458, 178, 141, 345, 158, 164, 459
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
