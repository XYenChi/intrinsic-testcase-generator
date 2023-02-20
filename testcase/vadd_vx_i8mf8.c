/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf8_t data1[] = {
    60, 191, 127, 47, 128, 206, 106, 83, 30, 211, 122, 226, 3, 160, 155, 47, 213, 50, 54, 158, 184, 211, 98, 166, 98, 178, 74, 7, 17, 86, 37, 253, 161, 13, 74, 126, 239, 234, 132, 203, 194, 1, 87, 37, 16, 106, 221, 0, 28, 3, 148, 196, 43, 174, 237, 11, 132, 148, 146, 22, 189, 223, 3, 88
    };
    const vint8mf8_t *in1 = &data1[0];
    vint8mf8_t data2[] = {
    255, 141, 105, 38, 253, 181, 26, 118, 101, 132, 134, 193, 225, 62, 193, 15, 104, 189, 171, 104, 214, 239, 147, 109, 114, 249, 187, 6, 154, 203, 250, 114, 159, 123, 81, 120, 75, 82, 58, 155, 103, 102, 134, 209, 147, 111, 227, 122, 87, 196, 62, 184, 100, 187, 169, 119, 98, 27, 65, 120, 51, 184, 244, 170
    };
    const vint8mf8_t *in2 = &data2[0];
    vint8mf8_t out_data[64];
    vint8mf8_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf8_t out = __riscv_vadd_vx_i8mf8 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf8_t golden[] = {
    315, 332, 232, 85, 381, 387, 132, 201, 131, 343, 256, 419, 228, 222, 348, 62, 317, 239, 225, 262, 398, 450, 245, 275, 212, 427, 261, 13, 171, 289, 287, 367, 320, 136, 155, 246, 314, 316, 190, 358, 297, 103, 221, 246, 163, 217, 448, 122, 115, 199, 210, 380, 143, 361, 406, 130, 230, 175, 211, 142, 240, 407, 247, 258
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
