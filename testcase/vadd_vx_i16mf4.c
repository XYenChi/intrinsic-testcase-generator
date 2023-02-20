/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16mf4_t data1[] = {
    233, 24, 187, 221, 13, 160, 161, 163, 15, 158, 147, 199, 255, 74, 229, 237, 182, 203, 133, 184, 17, 207, 171, 30, 142, 59, 240, 103, 125, 143, 99, 21, 138, 96, 228, 224, 128, 67, 126, 229, 49, 23, 95, 85, 207, 0, 67, 3, 7, 109, 6, 59, 184, 155, 240, 148, 149, 18, 84, 228, 59, 233, 196, 42
    };
    const vint16mf4_t *in1 = &data1[0];
    vint16mf4_t data2[] = {
    203, 44, 18, 102, 73, 216, 36, 186, 0, 98, 2, 213, 89, 156, 199, 9, 240, 141, 237, 243, 166, 173, 135, 138, 160, 220, 83, 28, 172, 122, 90, 217, 171, 23, 15, 220, 116, 183, 87, 40, 73, 200, 42, 235, 34, 180, 47, 62, 191, 231, 115, 116, 230, 146, 129, 130, 102, 75, 164, 24, 167, 35, 14, 112
    };
    const vint16mf4_t *in2 = &data2[0];
    vint16mf4_t out_data[64];
    vint16mf4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16mf4_t out = __riscv_vadd_vx_i16mf4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16mf4_t golden[] = {
    436, 68, 205, 323, 86, 376, 197, 349, 15, 256, 149, 412, 344, 230, 428, 246, 422, 344, 370, 427, 183, 380, 306, 168, 302, 279, 323, 131, 297, 265, 189, 238, 309, 119, 243, 444, 244, 250, 213, 269, 122, 223, 137, 320, 241, 180, 114, 65, 198, 340, 121, 175, 414, 301, 369, 278, 251, 93, 248, 252, 226, 268, 210, 154
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
