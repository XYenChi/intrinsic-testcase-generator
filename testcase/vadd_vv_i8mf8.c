/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf8_t data1[] = {
    244, 119, 90, 46, 122, 66, 67, 227, 232, 91, 216, 119, 72, 254, 187, 226, 66, 16, 220, 242, 147, 135, 132, 71, 72, 149, 35, 114, 223, 18, 147, 113, 35, 173, 189, 40, 213, 204, 186, 109, 180, 8, 237, 110, 100, 116, 42, 19, 240, 223, 219, 74, 83, 157, 99, 239, 14, 68, 127, 223, 23, 208, 180, 25
    };
    const vint8mf8_t *in1 = &data1[0];
    vint8mf8_t data2[] = {
    137, 63, 129, 236, 242, 243, 209, 145, 22, 112, 167, 35, 100, 237, 11, 62, 159, 89, 255, 73, 136, 239, 225, 214, 174, 91, 167, 255, 64, 195, 71, 82, 189, 145, 33, 64, 201, 183, 170, 255, 56, 42, 13, 160, 70, 15, 215, 237, 213, 225, 219, 219, 191, 227, 147, 131, 133, 3, 75, 249, 33, 97, 170, 5
    };
    const vint8mf8_t *in2 = &data2[0];
    vint8mf8_t out_data[64];
    vint8mf8_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf8_t out = __riscv_vadd_vv_i8mf8 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf8_t golden[] = {
    381, 182, 219, 282, 364, 309, 276, 372, 254, 203, 383, 154, 172, 491, 198, 288, 225, 105, 475, 315, 283, 374, 357, 285, 246, 240, 202, 369, 287, 213, 218, 195, 224, 318, 222, 104, 414, 387, 356, 364, 236, 50, 250, 270, 170, 131, 257, 256, 453, 448, 438, 293, 274, 384, 246, 370, 147, 71, 202, 472, 56, 305, 350, 30
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
