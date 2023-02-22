/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m8_t data1[] = {
    192, 37, 185, 164, 226, 57, 3, 98, 46, 147, 190, 210, 195, 52, 232, 241, 150, 169, 100, 108, 96, 104, 103, 175, 7, 111, 143, 200, 248, 134, 87, 53, 20, 39, 47, 227, 194, 2, 105, 206, 166, 165, 102, 241, 197, 153, 103, 170, 230, 214, 120, 153, 28, 214, 66, 212, 115, 117, 212, 202, 48, 60, 111, 186
    };
    const vint8m8_t *in1 = &data1[0];
    vint8m8_t data2[] = {
    67, 238, 170, 93, 156, 32, 61, 106, 45, 93, 2, 152, 92, 201, 54, 233, 119, 209, 202, 101, 216, 178, 246, 249, 250, 14, 96, 38, 90, 102, 235, 32, 0, 224, 188, 153, 105, 173, 210, 243, 91, 252, 187, 231, 108, 18, 147, 192, 86, 44, 238, 142, 204, 95, 107, 225, 90, 76, 88, 182, 55, 213, 82, 163
    };
    const vint8m8_t *in2 = &data2[0];
    vint8m8_t out_data[64];
    vint8m8_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m8_t out = __riscv_vadd_vv_i8m8 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m8_t golden[] = {
    259, 275, 355, 257, 382, 89, 64, 204, 91, 240, 192, 362, 287, 253, 286, 474, 269, 378, 302, 209, 312, 282, 349, 424, 257, 125, 239, 238, 338, 236, 322, 85, 20, 263, 235, 380, 299, 175, 315, 449, 257, 417, 289, 472, 305, 171, 250, 362, 316, 258, 358, 295, 232, 309, 173, 437, 205, 193, 300, 384, 103, 273, 193, 349
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