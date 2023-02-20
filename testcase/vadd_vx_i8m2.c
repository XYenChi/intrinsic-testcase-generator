/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m2_t data1[] = {
    207, 109, 231, 229, 181, 154, 49, 82, 130, 159, 226, 68, 131, 135, 11, 11, 36, 143, 15, 130, 214, 133, 75, 18, 12, 110, 80, 159, 211, 214, 167, 26, 168, 202, 166, 195, 163, 152, 71, 0, 205, 43, 1, 165, 140, 246, 160, 68, 180, 23, 171, 226, 172, 197, 168, 51, 51, 131, 110, 33, 147, 35, 26, 44
    };
    const vint8m2_t *in1 = &data1[0];
    vint8m2_t data2[] = {
    37, 69, 227, 43, 119, 246, 120, 43, 130, 194, 3, 193, 164, 148, 211, 212, 225, 148, 98, 42, 90, 69, 85, 162, 203, 62, 101, 243, 173, 159, 15, 64, 238, 170, 189, 69, 246, 150, 139, 174, 30, 7, 242, 44, 215, 162, 237, 58, 11, 141, 63, 231, 113, 57, 205, 200, 46, 41, 171, 240, 30, 87, 53, 80
    };
    const vint8m2_t *in2 = &data2[0];
    vint8m2_t out_data[64];
    vint8m2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m2_t out = __riscv_vadd_vx_i8m2 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m2_t golden[] = {
    244, 178, 458, 272, 300, 400, 169, 125, 260, 353, 229, 261, 295, 283, 222, 223, 261, 291, 113, 172, 304, 202, 160, 180, 215, 172, 181, 402, 384, 373, 182, 90, 406, 372, 355, 264, 409, 302, 210, 174, 235, 50, 243, 209, 355, 408, 397, 126, 191, 164, 234, 457, 285, 254, 373, 251, 97, 172, 281, 273, 177, 122, 79, 124
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
