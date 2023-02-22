/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m2_t data1[] = {
    26, 70, 23, 231, 155, 252, 242, 130, 168, 91, 124, 177, 123, 229, 243, 128, 225, 180, 135, 191, 100, 146, 229, 250, 195, 25, 59, 121, 213, 19, 14, 188, 22, 202, 220, 144, 135, 12, 174, 177, 191, 68, 239, 103, 235, 92, 119, 146, 217, 202, 102, 242, 92, 80, 199, 229, 222, 102, 241, 124, 245, 123, 54, 248
    };
    const vint32m2_t *in1 = &data1[0];
    vint32m2_t data2[] = {
    136, 9, 250, 16, 97, 8, 209, 220, 199, 43, 187, 166, 96, 181, 152, 254, 35, 57, 132, 121, 228, 143, 249, 38, 99, 230, 105, 132, 0, 99, 245, 185, 105, 27, 110, 199, 6, 17, 224, 55, 251, 176, 43, 218, 236, 17, 202, 147, 118, 219, 139, 209, 46, 158, 53, 53, 159, 237, 219, 24, 203, 181, 182, 231
    };
    const vint32m2_t *in2 = &data2[0];
    vint32m2_t out_data[] = {
    61, 21, 126, 212, 213, 132, 128, 106, 104, 4, 97, 31, 13, 18, 120, 149, 71, 62, 56, 85, 80, 19, 70, 26, 219, 61, 94, 185, 147, 249, 145, 255, 184, 93, 144, 193, 124, 89, 142, 125, 139, 227, 27, 61, 136, 200, 162, 107, 223, 199, 111, 249, 254, 202, 45, 17, 195, 37, 8, 217, 215, 127, 40, 142
    };
    vint32m2_t *out = &out_data[0];
    int masked[] = {
    1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32m2_t out = __riscv_vadd_vx_i32m2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint32m2_t golden[] = {
    162, 79, 273, 247, 213, 260, 451, 106, 367, 4, 311, 343, 13, 410, 120, 149, 71, 237, 267, 85, 80, 289, 478, 288, 219, 255, 94, 185, 147, 118, 145, 255, 127, 229, 330, 343, 141, 29, 398, 125, 139, 244, 282, 61, 471, 200, 162, 293, 223, 421, 241, 249, 254, 202, 45, 17, 195, 339, 460, 148, 448, 304, 236, 479
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