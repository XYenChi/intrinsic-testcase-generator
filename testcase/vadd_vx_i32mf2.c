/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32mf2_t data1[] = {
    119, 221, 215, 205, 37, 101, 16, 237, 230, 222, 94, 178, 114, 153, 250, 193, 197, 241, 236, 209, 26, 156, 124, 25, 150, 226, 150, 0, 205, 119, 192, 109, 14, 243, 191, 113, 238, 5, 117, 176, 9, 56, 13, 5, 117, 89, 64, 153, 163, 177, 139, 254, 163, 182, 60, 194, 192, 23, 133, 181, 22, 174, 177, 15
    };
    const vint32mf2_t *in1 = &data1[0];
    vint32mf2_t data2[] = {
    101, 139, 113, 234, 112, 67, 102, 118, 10, 59, 120, 37, 63, 59, 221, 71, 184, 234, 106, 180, 74, 210, 49, 1, 16, 77, 151, 76, 251, 35, 235, 60, 176, 246, 62, 19, 139, 142, 181, 122, 5, 138, 113, 211, 94, 174, 99, 172, 36, 218, 155, 195, 53, 32, 61, 54, 208, 100, 63, 42, 167, 206, 46, 57
    };
    const vint32mf2_t *in2 = &data2[0];
    vint32mf2_t out_data[64];
    vint32mf2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32mf2_t out = __riscv_vadd_vx_i32mf2 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32mf2_t golden[] = {
    220, 360, 328, 439, 149, 168, 118, 355, 240, 281, 214, 215, 177, 212, 471, 264, 381, 475, 342, 389, 100, 366, 173, 26, 166, 303, 301, 76, 456, 154, 427, 169, 190, 489, 253, 132, 377, 147, 298, 298, 14, 194, 126, 216, 211, 263, 163, 325, 199, 395, 294, 449, 216, 214, 121, 248, 400, 123, 196, 223, 189, 380, 223, 72
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
