/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16mf2_t data1[] = {
    165, 204, 155, 230, 92, 27, 164, 191, 129, 52, 28, 240, 27, 32, 67, 195, 80, 201, 155, 113, 35, 23, 105, 151, 112, 16, 68, 203, 181, 169, 228, 244, 84, 95, 155, 112, 240, 35, 70, 22, 22, 230, 102, 137, 154, 194, 227, 238, 141, 99, 73, 212, 208, 31, 27, 189, 150, 128, 250, 187, 206, 141, 146, 209
    };
    const vint16mf2_t *in1 = &data1[0];
    vint16mf2_t data2[] = {
    165, 237, 169, 90, 214, 204, 88, 177, 128, 95, 104, 134, 189, 12, 121, 88, 145, 11, 41, 1, 33, 220, 39, 54, 250, 91, 75, 177, 9, 90, 27, 240, 233, 136, 61, 107, 136, 249, 234, 17, 171, 163, 25, 186, 131, 222, 177, 249, 157, 155, 75, 87, 137, 83, 8, 215, 135, 244, 78, 42, 21, 207, 143, 202
    };
    const vint16mf2_t *in2 = &data2[0];
    vint16mf2_t out_data[64];
    vint16mf2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16mf2_t out = __riscv_vadd_vv_i16mf2 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16mf2_t golden[] = {
    330, 441, 324, 320, 306, 231, 252, 368, 257, 147, 132, 374, 216, 44, 188, 283, 225, 212, 196, 114, 68, 243, 144, 205, 362, 107, 143, 380, 190, 259, 255, 484, 317, 231, 216, 219, 376, 284, 304, 39, 193, 393, 127, 323, 285, 416, 404, 487, 298, 254, 148, 299, 345, 114, 35, 404, 285, 372, 328, 229, 227, 348, 289, 411
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
