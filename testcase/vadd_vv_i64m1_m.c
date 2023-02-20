/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m1_t data1[] = {
    51, 223, 20, 114, 26, 248, 37, 52, 229, 138, 157, 139, 105, 36, 200, 22, 25, 92, 142, 115, 118, 192, 110, 180, 250, 2, 138, 9, 237, 4, 209, 202, 33, 153, 147, 39, 242, 39, 29, 219, 180, 166, 159, 179, 97, 104, 198, 116, 198, 110, 225, 203, 111, 27, 6, 8, 229, 9, 209, 202, 70, 216, 67, 217
    };
    const vint64m1_t *in1 = &data1[0];
    vint64m1_t data2[] = {
    245, 132, 219, 36, 191, 28, 34, 74, 54, 210, 136, 55, 76, 113, 90, 15, 187, 159, 152, 197, 4, 233, 176, 124, 125, 64, 167, 107, 127, 156, 117, 224, 105, 146, 123, 26, 9, 160, 209, 162, 99, 47, 123, 175, 228, 176, 255, 156, 219, 95, 17, 190, 10, 225, 249, 113, 235, 16, 33, 112, 85, 166, 148, 22
    };
    const vint64m1_t *in2 = &data2[0];
    vint64m1_t out_data[] = {
    233, 121, 222, 33, 26, 159, 178, 169, 71, 5, 12, 21, 247, 47, 233, 45, 120, 82, 214, 203, 99, 55, 236, 155, 34, 199, 2, 0, 119, 221, 40, 214, 181, 152, 29, 99, 244, 39, 240, 216, 5, 59, 170, 162, 27, 164, 97, 75, 176, 130, 49, 100, 241, 119, 137, 85, 50, 167, 115, 128, 94, 42, 91, 21
    };
    vint64m1_t *out = &out_data[0];
    int masked[] = {
    1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint64m1_t out = __riscv_vadd_vv_i64m1_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint64m1_t golden[] = {
    296, 121, 239, 150, 217, 276, 178, 126, 283, 5, 293, 21, 247, 149, 233, 45, 212, 251, 294, 312, 99, 55, 286, 155, 375, 66, 305, 116, 119, 160, 326, 426, 138, 152, 29, 99, 251, 199, 240, 381, 5, 213, 170, 162, 27, 164, 97, 272, 417, 130, 242, 393, 121, 119, 137, 85, 50, 167, 115, 128, 94, 42, 91, 21
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
