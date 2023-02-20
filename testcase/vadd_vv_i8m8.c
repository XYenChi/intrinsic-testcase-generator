/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m8_t data1[] = {
    28, 60, 20, 162, 97, 63, 72, 197, 176, 209, 125, 166, 245, 19, 131, 174, 63, 72, 157, 218, 78, 186, 187, 237, 178, 167, 4, 4, 206, 157, 192, 19, 126, 89, 239, 65, 2, 156, 44, 223, 139, 96, 41, 170, 75, 126, 244, 47, 233, 30, 65, 14, 118, 167, 80, 178, 129, 52, 217, 90, 142, 87, 73, 216
    };
    const vint8m8_t *in1 = &data1[0];
    vint8m8_t data2[] = {
    16, 168, 194, 81, 151, 74, 143, 34, 60, 195, 246, 169, 2, 162, 73, 114, 206, 96, 153, 209, 84, 14, 34, 254, 52, 121, 167, 2, 11, 145, 211, 13, 237, 215, 190, 203, 207, 179, 167, 182, 184, 125, 180, 46, 225, 98, 172, 19, 249, 179, 21, 162, 43, 88, 2, 150, 198, 245, 18, 184, 109, 48, 43, 33
    };
    const vint8m8_t *in2 = &data2[0];
    vint8m8_t out_data[64];
    vint8m8_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m8_t out = __riscv_vadd_vv_i8m8 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m8_t golden[] = {
    44, 228, 214, 243, 248, 137, 215, 231, 236, 404, 371, 335, 247, 181, 204, 288, 269, 168, 310, 427, 162, 200, 221, 491, 230, 288, 171, 6, 217, 302, 403, 32, 363, 304, 429, 268, 209, 335, 211, 405, 323, 221, 221, 216, 300, 224, 416, 66, 482, 209, 86, 176, 161, 255, 82, 328, 327, 297, 235, 274, 251, 135, 116, 249
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
