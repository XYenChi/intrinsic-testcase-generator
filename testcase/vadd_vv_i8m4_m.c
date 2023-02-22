/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m4_t data1[] = {
    215, 136, 22, 2, 227, 53, 78, 70, 211, 118, 190, 4, 91, 249, 103, 67, 50, 26, 163, 55, 105, 154, 11, 219, 167, 198, 56, 194, 109, 88, 236, 252, 145, 219, 209, 129, 73, 199, 93, 46, 45, 5, 254, 196, 17, 113, 144, 45, 27, 195, 249, 199, 41, 54, 230, 136, 75, 33, 52, 140, 187, 211, 200, 176
    };
    const vint8m4_t *in1 = &data1[0];
    vint8m4_t data2[] = {
    193, 147, 142, 45, 142, 245, 203, 145, 221, 9, 189, 224, 187, 146, 132, 230, 11, 48, 136, 222, 28, 58, 65, 16, 107, 109, 156, 230, 61, 165, 105, 86, 197, 82, 253, 230, 240, 132, 20, 24, 193, 156, 78, 179, 147, 150, 221, 100, 63, 216, 196, 149, 20, 100, 23, 230, 92, 0, 249, 247, 165, 109, 91, 149
    };
    const vint8m4_t *in2 = &data2[0];
    vint8m4_t out_data[] = {
    87, 168, 65, 0, 86, 0, 42, 12, 224, 65, 33, 43, 23, 211, 36, 39, 26, 106, 190, 123, 5, 254, 216, 245, 14, 52, 206, 75, 53, 137, 23, 12, 14, 44, 236, 25, 143, 103, 106, 163, 66, 116, 167, 194, 36, 86, 54, 206, 124, 219, 114, 57, 23, 237, 132, 31, 90, 34, 5, 150, 130, 236, 150, 101
    };
    vint8m4_t *out = &out_data[0];
    int masked[] = {
    0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m4_t out = __riscv_vadd_vv_i8m4_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint8m4_t golden[] = {
    87, 283, 65, 47, 369, 0, 281, 215, 432, 65, 379, 228, 23, 395, 235, 39, 26, 74, 190, 123, 5, 212, 76, 245, 274, 307, 212, 75, 170, 137, 23, 338, 342, 301, 462, 25, 143, 103, 106, 70, 66, 161, 167, 375, 164, 86, 365, 206, 124, 219, 445, 57, 23, 154, 253, 366, 167, 33, 301, 387, 352, 320, 150, 101
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