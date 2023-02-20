/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m8_t data1[] = {
    53, 42, 243, 55, 61, 145, 40, 46, 26, 173, 86, 13, 51, 87, 163, 0, 96, 72, 74, 141, 147, 253, 229, 139, 163, 211, 58, 48, 201, 172, 68, 113, 199, 29, 209, 102, 218, 199, 91, 29, 236, 22, 73, 96, 41, 166, 111, 119, 102, 43, 203, 12, 232, 8, 242, 103, 121, 192, 14, 139, 93, 143, 68, 95
    };
    const vint32m8_t *in1 = &data1[0];
    vint32m8_t data2[] = {
    89, 104, 224, 146, 252, 170, 255, 51, 55, 216, 68, 44, 200, 155, 182, 39, 98, 14, 186, 190, 177, 244, 40, 71, 95, 102, 209, 141, 107, 53, 47, 208, 160, 57, 106, 246, 31, 175, 13, 193, 188, 60, 42, 160, 118, 102, 33, 44, 64, 14, 113, 57, 89, 172, 221, 0, 252, 38, 112, 5, 220, 230, 106, 37
    };
    const vint32m8_t *in2 = &data2[0];
    vint32m8_t out_data[] = {
    201, 211, 21, 239, 121, 67, 201, 12, 44, 86, 139, 161, 55, 112, 76, 206, 244, 92, 28, 161, 111, 4, 70, 36, 75, 229, 226, 250, 89, 180, 224, 2, 63, 130, 232, 248, 240, 8, 204, 204, 208, 130, 25, 52, 162, 229, 65, 62, 78, 164, 220, 157, 171, 149, 125, 28, 98, 192, 234, 19, 125, 130, 126, 225
    };
    vint32m8_t *out = &out_data[0];
    int masked[] = {
    1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32m8_t out = __riscv_vadd_vv_i32m8_m (, mask, data1, data264);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint32m8_t golden[] = {
    142, 211, 467, 201, 313, 315, 201, 12, 44, 389, 139, 161, 55, 112, 345, 206, 194, 92, 260, 331, 324, 4, 70, 210, 258, 229, 267, 189, 308, 180, 224, 321, 63, 86, 315, 248, 249, 374, 104, 222, 424, 82, 25, 256, 159, 268, 65, 163, 166, 164, 220, 157, 171, 180, 125, 103, 373, 230, 126, 144, 125, 130, 174, 132
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
