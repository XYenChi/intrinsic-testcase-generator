/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf2_t data1[] = {
    132, 105, 80, 252, 93, 82, 133, 26, 200, 35, 58, 142, 16, 84, 245, 7, 49, 47, 222, 18, 193, 233, 137, 229, 224, 104, 5, 68, 248, 240, 213, 95, 165, 38, 187, 102, 166, 65, 95, 16, 93, 29, 121, 21, 233, 113, 154, 22, 252, 191, 217, 228, 89, 209, 97, 165, 153, 70, 180, 226, 230, 216, 67, 190
    };
    const vint8mf2_t *in1 = &data1[0];
    vint8mf2_t data2[] = {
    225, 208, 243, 165, 88, 145, 116, 43, 232, 203, 163, 18, 113, 66, 47, 80, 199, 129, 32, 4, 111, 169, 72, 73, 249, 97, 206, 67, 180, 65, 146, 196, 66, 209, 153, 124, 152, 69, 92, 41, 35, 97, 76, 185, 224, 228, 190, 27, 255, 167, 9, 162, 3, 58, 136, 117, 142, 199, 142, 186, 228, 146, 128, 141
    };
    const vint8mf2_t *in2 = &data2[0];
    vint8mf2_t out_data[64];
    vint8mf2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf2_t out = __riscv_vadd_vv_i8mf2 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf2_t golden[] = {
    357, 313, 323, 417, 181, 227, 249, 69, 432, 238, 221, 160, 129, 150, 292, 87, 248, 176, 254, 22, 304, 402, 209, 302, 473, 201, 211, 135, 428, 305, 359, 291, 231, 247, 340, 226, 318, 134, 187, 57, 128, 126, 197, 206, 457, 341, 344, 49, 507, 358, 226, 390, 92, 267, 233, 282, 295, 269, 322, 412, 458, 362, 195, 331
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
