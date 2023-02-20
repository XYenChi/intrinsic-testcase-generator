/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32mf2_t data1[] = {
    55, 34, 40, 96, 97, 244, 144, 161, 208, 123, 203, 84, 179, 233, 60, 106, 204, 7, 208, 80, 50, 60, 96, 86, 34, 81, 184, 210, 236, 74, 192, 161, 96, 19, 251, 238, 90, 39, 128, 109, 203, 46, 130, 221, 184, 2, 43, 145, 148, 33, 128, 103, 90, 90, 175, 143, 131, 68, 202, 17, 120, 140, 180, 194
    };
    const vint32mf2_t *in1 = &data1[0];
    vint32mf2_t data2[] = {
    204, 149, 186, 187, 70, 188, 190, 174, 255, 242, 1, 136, 234, 93, 76, 186, 220, 11, 18, 139, 140, 17, 164, 13, 193, 191, 255, 236, 41, 89, 152, 193, 56, 84, 220, 85, 50, 87, 245, 144, 169, 23, 40, 44, 137, 4, 247, 169, 251, 195, 242, 147, 1, 43, 74, 197, 92, 164, 221, 205, 235, 238, 218, 162
    };
    const vint32mf2_t *in2 = &data2[0];
    vint32mf2_t out_data[64];
    vint32mf2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32mf2_t out = __riscv_vadd_vv_i32mf2 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32mf2_t golden[] = {
    259, 183, 226, 283, 167, 432, 334, 335, 463, 365, 204, 220, 413, 326, 136, 292, 424, 18, 226, 219, 190, 77, 260, 99, 227, 272, 439, 446, 277, 163, 344, 354, 152, 103, 471, 323, 140, 126, 373, 253, 372, 69, 170, 265, 321, 6, 290, 314, 399, 228, 370, 250, 91, 133, 249, 340, 223, 232, 423, 222, 355, 378, 398, 356
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
