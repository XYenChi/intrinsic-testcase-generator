/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m2_t data1[] = {
    25, 106, 91, 222, 18, 76, 138, 231, 22, 201, 250, 121, 78, 130, 218, 126, 196, 216, 245, 170, 59, 136, 136, 57, 202, 166, 189, 215, 143, 27, 69, 217, 123, 165, 217, 46, 170, 10, 72, 197, 220, 48, 223, 13, 13, 68, 173, 39, 66, 43, 180, 149, 24, 138, 15, 251, 58, 117, 211, 157, 121, 56, 194, 26
    };
    const vint8m2_t *in1 = &data1[0];
    vint8m2_t data2[] = {
    33, 253, 205, 0, 63, 216, 248, 182, 21, 16, 55, 0, 102, 176, 21, 88, 165, 226, 163, 157, 146, 133, 73, 26, 7, 221, 88, 82, 113, 139, 43, 146, 148, 1, 209, 77, 72, 210, 184, 147, 249, 124, 101, 70, 160, 115, 86, 238, 3, 134, 18, 25, 129, 162, 246, 239, 138, 91, 137, 140, 107, 35, 26, 81
    };
    const vint8m2_t *in2 = &data2[0];
    vint8m2_t out_data[] = {
    65, 255, 203, 252, 247, 37, 102, 31, 121, 14, 172, 89, 165, 245, 152, 186, 43, 226, 192, 209, 215, 149, 74, 180, 100, 10, 183, 231, 21, 211, 99, 89, 97, 127, 83, 187, 49, 16, 9, 21, 193, 245, 49, 59, 71, 191, 235, 241, 61, 23, 216, 117, 20, 255, 254, 42, 179, 63, 103, 138, 77, 73, 200, 250
    };
    vint8m2_t *out = &out_data[0];
    int masked[] = {
    1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m2_t out = __riscv_vadd_vv_i8m2_m (, mask, data1, data264);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint8m2_t golden[] = {
    58, 359, 203, 252, 81, 37, 386, 413, 43, 217, 305, 89, 165, 245, 152, 214, 43, 226, 192, 209, 205, 149, 74, 83, 209, 387, 183, 297, 256, 166, 112, 363, 271, 127, 83, 187, 49, 16, 256, 344, 469, 172, 324, 59, 173, 191, 259, 277, 69, 177, 198, 174, 153, 255, 261, 490, 179, 63, 103, 138, 77, 91, 220, 250
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
