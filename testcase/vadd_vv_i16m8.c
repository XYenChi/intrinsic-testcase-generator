/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m8_t data1[] = {
    159, 176, 80, 163, 253, 129, 57, 68, 71, 208, 168, 214, 95, 255, 41, 63, 76, 134, 73, 233, 156, 47, 111, 62, 193, 234, 47, 233, 117, 185, 230, 102, 124, 223, 40, 143, 17, 155, 40, 123, 111, 140, 180, 47, 196, 148, 105, 186, 13, 98, 218, 202, 132, 221, 230, 162, 159, 47, 223, 53, 206, 175, 33, 216
    };
    const vint16m8_t *in1 = &data1[0];
    vint16m8_t data2[] = {
    24, 253, 90, 173, 54, 154, 184, 140, 65, 187, 16, 229, 177, 120, 152, 41, 158, 126, 80, 37, 61, 69, 194, 4, 194, 23, 28, 11, 161, 110, 170, 108, 132, 210, 123, 248, 137, 52, 204, 228, 190, 221, 57, 67, 28, 41, 73, 105, 169, 175, 50, 203, 9, 24, 38, 98, 194, 162, 178, 59, 174, 103, 73, 200
    };
    const vint16m8_t *in2 = &data2[0];
    vint16m8_t out_data[64];
    vint16m8_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m8_t out = __riscv_vadd_vv_i16m8 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16m8_t golden[] = {
    183, 429, 170, 336, 307, 283, 241, 208, 136, 395, 184, 443, 272, 375, 193, 104, 234, 260, 153, 270, 217, 116, 305, 66, 387, 257, 75, 244, 278, 295, 400, 210, 256, 433, 163, 391, 154, 207, 244, 351, 301, 361, 237, 114, 224, 189, 178, 291, 182, 273, 268, 405, 141, 245, 268, 260, 353, 209, 401, 112, 380, 278, 106, 416
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
