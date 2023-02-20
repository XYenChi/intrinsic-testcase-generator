/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16mf4_t data1[] = {
    14, 109, 16, 45, 148, 20, 26, 204, 202, 175, 103, 135, 205, 176, 120, 95, 151, 129, 28, 168, 30, 190, 81, 188, 96, 128, 208, 200, 42, 197, 126, 158, 195, 133, 236, 147, 80, 173, 94, 12, 201, 80, 226, 161, 210, 61, 90, 95, 112, 168, 86, 247, 80, 23, 24, 41, 76, 126, 117, 188, 247, 88, 127, 77
    };
    const vint16mf4_t *in1 = &data1[0];
    vint16mf4_t data2[] = {
    254, 115, 137, 20, 95, 115, 120, 251, 24, 126, 64, 173, 66, 228, 40, 221, 254, 6, 230, 142, 68, 139, 66, 160, 154, 189, 97, 15, 237, 249, 145, 138, 88, 104, 241, 220, 169, 116, 156, 53, 201, 179, 165, 162, 40, 233, 75, 233, 209, 250, 143, 53, 239, 0, 111, 15, 36, 91, 76, 194, 245, 148, 231, 156
    };
    const vint16mf4_t *in2 = &data2[0];
    vint16mf4_t out_data[64];
    vint16mf4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16mf4_t out = __riscv_vadd_vx_i16mf4 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16mf4_t golden[] = {
    268, 224, 153, 65, 243, 135, 146, 455, 226, 301, 167, 308, 271, 404, 160, 316, 405, 135, 258, 310, 98, 329, 147, 348, 250, 317, 305, 215, 279, 446, 271, 296, 283, 237, 477, 367, 249, 289, 250, 65, 402, 259, 391, 323, 250, 294, 165, 328, 321, 418, 229, 300, 319, 23, 135, 56, 112, 217, 193, 382, 492, 236, 358, 233
    };
    int fail = 0;
    for (int i = 0; i < 64; i++)
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
