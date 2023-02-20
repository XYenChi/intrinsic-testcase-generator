/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf4_t data1[] = {
    254, 202, 224, 57, 255, 96, 180, 133, 185, 107, 162, 29, 35, 44, 17, 115, 255, 184, 90, 127, 60, 102, 40, 168, 248, 158, 132, 101, 228, 149, 63, 122, 95, 104, 251, 64, 194, 109, 108, 76, 61, 198, 189, 171, 60, 56, 181, 176, 141, 187, 16, 165, 97, 169, 48, 65, 173, 65, 234, 250, 223, 43, 15, 42
    };
    const vint8mf4_t *in1 = &data1[0];
    vint8mf4_t data2[] = {
    17, 10, 195, 230, 83, 118, 85, 19, 68, 159, 6, 219, 75, 216, 173, 250, 183, 238, 143, 135, 238, 194, 23, 77, 220, 242, 97, 131, 9, 106, 250, 242, 125, 23, 134, 118, 155, 31, 20, 188, 70, 144, 74, 158, 233, 10, 240, 4, 208, 61, 249, 171, 34, 165, 73, 106, 235, 166, 9, 120, 123, 102, 213, 225
    };
    const vint8mf4_t *in2 = &data2[0];
    vint8mf4_t out_data[64];
    vint8mf4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf4_t out = __riscv_vadd_vx_i8mf4 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf4_t golden[] = {
    271, 212, 419, 287, 338, 214, 265, 152, 253, 266, 168, 248, 110, 260, 190, 365, 438, 422, 233, 262, 298, 296, 63, 245, 468, 400, 229, 232, 237, 255, 313, 364, 220, 127, 385, 182, 349, 140, 128, 264, 131, 342, 263, 329, 293, 66, 421, 180, 349, 248, 265, 336, 131, 334, 121, 171, 408, 231, 243, 370, 346, 145, 228, 267
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
