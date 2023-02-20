/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m2_t data1[] = {
    111, 232, 22, 4, 80, 194, 125, 20, 63, 100, 70, 164, 253, 40, 223, 20, 74, 205, 97, 227, 123, 155, 120, 137, 223, 44, 26, 136, 161, 17, 254, 119, 64, 45, 20, 79, 43, 201, 243, 126, 100, 37, 67, 33, 197, 164, 153, 116, 54, 93, 231, 63, 84, 122, 252, 17, 111, 37, 97, 101, 242, 62, 225, 169
    };
    const vint16m2_t *in1 = &data1[0];
    vint16m2_t data2[] = {
    185, 222, 94, 201, 108, 155, 50, 142, 9, 70, 43, 65, 85, 196, 16, 176, 152, 116, 231, 72, 36, 127, 243, 172, 243, 118, 43, 140, 86, 253, 174, 156, 247, 160, 193, 14, 68, 240, 66, 120, 52, 204, 51, 78, 24, 18, 91, 178, 127, 130, 130, 249, 43, 149, 130, 22, 193, 87, 34, 178, 167, 149, 127, 241
    };
    const vint16m2_t *in2 = &data2[0];
    vint16m2_t out_data[] = {
    132, 222, 103, 199, 175, 147, 165, 180, 195, 174, 65, 156, 221, 72, 43, 130, 121, 50, 132, 77, 59, 199, 131, 178, 182, 224, 225, 239, 207, 135, 125, 77, 162, 113, 95, 218, 190, 150, 116, 185, 148, 90, 225, 59, 143, 226, 4, 238, 200, 184, 12, 139, 34, 106, 103, 76, 193, 122, 177, 147, 200, 164, 147, 1
    };
    vint16m2_t *out = &out_data[0];
    int masked[] = {
    0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m2_t out = __riscv_vadd_vv_i16m2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint16m2_t golden[] = {
    132, 454, 103, 199, 175, 147, 175, 162, 72, 170, 65, 156, 338, 72, 239, 130, 226, 50, 328, 77, 159, 282, 131, 309, 182, 162, 69, 276, 207, 135, 428, 275, 311, 113, 95, 93, 190, 441, 116, 246, 152, 90, 225, 111, 221, 226, 244, 294, 200, 184, 361, 139, 127, 271, 103, 76, 193, 124, 177, 279, 200, 211, 352, 1
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
