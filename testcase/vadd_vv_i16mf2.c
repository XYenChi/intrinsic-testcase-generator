/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16mf2_t data1[] = {
    18, 239, 129, 82, 190, 243, 133, 168, 19, 247, 42, 147, 23, 17, 209, 166, 0, 190, 217, 10, 228, 158, 101, 103, 57, 232, 22, 97, 50, 72, 27, 18, 207, 212, 42, 198, 146, 18, 41, 225, 173, 120, 187, 11, 231, 189, 94, 71, 53, 236, 163, 3, 241, 38, 90, 159, 33, 113, 150, 140, 89, 76, 224, 235
    };
    const vint16mf2_t *in1 = &data1[0];
    vint16mf2_t data2[] = {
    55, 21, 96, 104, 78, 156, 102, 141, 169, 128, 144, 68, 18, 246, 226, 229, 227, 90, 190, 189, 244, 185, 154, 83, 253, 187, 247, 40, 43, 223, 218, 40, 95, 64, 122, 187, 207, 114, 176, 244, 157, 94, 11, 141, 31, 63, 135, 234, 243, 163, 140, 78, 194, 216, 178, 163, 181, 66, 208, 39, 200, 229, 244, 92
    };
    const vint16mf2_t *in2 = &data2[0];
    vint16mf2_t out_data[64];
    vint16mf2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16mf2_t out = __riscv_vadd_vv_i16mf2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16mf2_t golden[] = {
    73, 260, 225, 186, 268, 399, 235, 309, 188, 375, 186, 215, 41, 263, 435, 395, 227, 280, 407, 199, 472, 343, 255, 186, 310, 419, 269, 137, 93, 295, 245, 58, 302, 276, 164, 385, 353, 132, 217, 469, 330, 214, 198, 152, 262, 252, 229, 305, 296, 399, 303, 81, 435, 254, 268, 322, 214, 179, 358, 179, 289, 305, 468, 327
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
