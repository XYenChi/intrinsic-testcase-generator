/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m1_t data1[] = {
    221, 70, 117, 110, 63, 93, 168, 147, 52, 239, 217, 223, 31, 164, 167, 157, 94, 58, 139, 18, 2, 145, 47, 163, 108, 127, 58, 178, 37, 198, 71, 112, 204, 230, 181, 109, 226, 70, 31, 208, 164, 213, 214, 158, 96, 231, 66, 205, 222, 98, 201, 124, 206, 193, 230, 17, 143, 180, 37, 224, 119, 172, 88, 114
    };
    const vint32m1_t *in1 = &data1[0];
    vint32m1_t data2[] = {
    45, 88, 129, 98, 134, 55, 40, 36, 85, 117, 38, 155, 56, 220, 90, 180, 115, 101, 170, 233, 9, 82, 101, 188, 141, 95, 46, 184, 186, 102, 21, 124, 134, 103, 255, 244, 183, 119, 88, 150, 204, 44, 201, 87, 188, 40, 166, 222, 147, 203, 232, 61, 13, 48, 233, 184, 15, 160, 208, 205, 12, 111, 161, 215
    };
    const vint32m1_t *in2 = &data2[0];
    vint32m1_t out_data[64];
    vint32m1_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32m1_t out = __riscv_vadd_vx_i32m1 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32m1_t golden[] = {
    266, 158, 246, 208, 197, 148, 208, 183, 137, 356, 255, 378, 87, 384, 257, 337, 209, 159, 309, 251, 11, 227, 148, 351, 249, 222, 104, 362, 223, 300, 92, 236, 338, 333, 436, 353, 409, 189, 119, 358, 368, 257, 415, 245, 284, 271, 232, 427, 369, 301, 433, 185, 219, 241, 463, 201, 158, 340, 245, 429, 131, 283, 249, 329
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