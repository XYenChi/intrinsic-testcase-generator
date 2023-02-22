/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m1_t data1[] = {
    222, 114, 38, 156, 143, 143, 104, 113, 14, 233, 80, 165, 124, 110, 5, 201, 199, 214, 61, 209, 97, 76, 140, 95, 168, 188, 73, 121, 170, 87, 242, 37, 139, 66, 9, 198, 169, 239, 99, 201, 226, 151, 230, 103, 196, 223, 185, 50, 113, 246, 211, 214, 182, 115, 116, 153, 107, 122, 86, 157, 70, 225, 85, 149
    };
    const vint16m1_t *in1 = &data1[0];
    vint16m1_t data2[] = {
    147, 186, 33, 72, 6, 0, 210, 145, 235, 222, 212, 95, 18, 104, 51, 99, 195, 144, 106, 124, 153, 59, 57, 77, 105, 63, 251, 65, 112, 72, 68, 121, 77, 169, 87, 228, 55, 43, 109, 82, 33, 10, 242, 90, 101, 180, 19, 57, 228, 189, 203, 187, 30, 198, 43, 241, 86, 70, 191, 15, 212, 150, 50, 194
    };
    const vint16m1_t *in2 = &data2[0];
    vint16m1_t out_data[64];
    vint16m1_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m1_t out = __riscv_vadd_vv_i16m1 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16m1_t golden[] = {
    369, 300, 71, 228, 149, 143, 314, 258, 249, 455, 292, 260, 142, 214, 56, 300, 394, 358, 167, 333, 250, 135, 197, 172, 273, 251, 324, 186, 282, 159, 310, 158, 216, 235, 96, 426, 224, 282, 208, 283, 259, 161, 472, 193, 297, 403, 204, 107, 341, 435, 414, 401, 212, 313, 159, 394, 193, 192, 277, 172, 282, 375, 135, 343
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