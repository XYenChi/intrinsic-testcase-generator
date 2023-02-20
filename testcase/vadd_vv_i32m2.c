/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m2_t data1[] = {
    163, 209, 219, 168, 124, 211, 105, 213, 8, 160, 190, 161, 95, 228, 89, 103, 139, 70, 55, 41, 1, 85, 254, 2, 108, 76, 212, 115, 248, 159, 248, 226, 9, 183, 29, 6, 67, 174, 128, 22, 81, 139, 224, 199, 30, 77, 15, 61, 67, 198, 199, 107, 21, 81, 75, 187, 93, 6, 240, 226, 211, 103, 74, 196
    };
    const vint32m2_t *in1 = &data1[0];
    vint32m2_t data2[] = {
    216, 144, 72, 150, 0, 241, 182, 46, 138, 190, 20, 222, 17, 123, 99, 73, 228, 126, 77, 30, 178, 81, 165, 53, 164, 55, 67, 29, 133, 129, 152, 182, 62, 165, 190, 85, 89, 135, 246, 255, 253, 116, 1, 181, 11, 219, 63, 144, 231, 244, 139, 178, 34, 205, 128, 233, 208, 98, 181, 133, 244, 243, 229, 164
    };
    const vint32m2_t *in2 = &data2[0];
    vint32m2_t out_data[64];
    vint32m2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32m2_t out = __riscv_vadd_vv_i32m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32m2_t golden[] = {
    379, 353, 291, 318, 124, 452, 287, 259, 146, 350, 210, 383, 112, 351, 188, 176, 367, 196, 132, 71, 179, 166, 419, 55, 272, 131, 279, 144, 381, 288, 400, 408, 71, 348, 219, 91, 156, 309, 374, 277, 334, 255, 225, 380, 41, 296, 78, 205, 298, 442, 338, 285, 55, 286, 203, 420, 301, 104, 421, 359, 455, 346, 303, 360
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
