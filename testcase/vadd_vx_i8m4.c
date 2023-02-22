/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m4_t data1[] = {
    213, 207, 173, 107, 187, 90, 57, 178, 164, 165, 110, 89, 60, 9, 0, 172, 248, 149, 210, 22, 56, 253, 33, 80, 55, 119, 222, 239, 65, 147, 82, 156, 213, 254, 111, 255, 250, 5, 61, 171, 73, 37, 23, 218, 173, 56, 165, 25, 45, 145, 207, 89, 75, 195, 64, 67, 188, 125, 145, 21, 181, 70, 130, 234
    };
    const vint8m4_t *in1 = &data1[0];
    vint8m4_t data2[] = {
    53, 114, 225, 92, 98, 80, 130, 1, 136, 206, 102, 229, 76, 154, 78, 211, 74, 49, 36, 202, 88, 252, 97, 134, 117, 36, 213, 176, 8, 35, 99, 26, 103, 249, 230, 153, 194, 201, 252, 118, 136, 214, 256, 21, 241, 104, 95, 20, 18, 109, 200, 71, 125, 176, 180, 108, 168, 214, 70, 34, 159, 61, 12, 112
    };
    const vint8m4_t *in2 = &data2[0];
    vint8m4_t out_data[64];
    vint8m4_t *out = &out_data[0];
    for (int n = 64, Q_element = 8;n >= 0; n -= Q_element) {
        vint8m4_t out = __riscv_vadd_vx_i8m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m4_t golden[] = {
    266, 321, 398, 199, 285, 170, 187, 179, 300, 371, 212, 318, 136, 163, 78, 383, 322, 198, 246, 224, 144, 505, 130, 214, 172, 155, 435, 415, 73, 182, 181, 182, 316, 503, 341, 408, 444, 206, 313, 289, 209, 251, 279, 239, 414, 160, 260, 45, 63, 254, 407, 160, 200, 371, 244, 175, 356, 339, 215, 55, 340, 131, 142, 346
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
}
