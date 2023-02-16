/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    201, 127, 22, 254, 176, 190, 204, 158, 248, 95, 123, 126, 33, 109, 46, 216, 67, 254, 127, 193, 217, 134, 190, 0, 216, 54, 124, 215, 191, 23, 22, 52, 111, 131, 213, 117, 24, 143, 67, 244, 165, 9, 154, 99, 19, 202, 55, 147, 53, 195, 45, 198, 87, 80, 248, 253, 80, 246, 237, 222, 224, 225, 133, 218
    };
    const int *in1 = &data1[0];
    int data2[] = {
    37, 105, 91, 206, 183, 167, 74, 152, 63, 93, 134, 56, 58, 187, 243, 67, 192, 160, 179, 192, 37, 97, 136, 247, 78, 105, 241, 183, 33, 206, 175, 189, 180, 68, 73, 201, 64, 5, 138, 40, 141, 109, 122, 223, 153, 119, 93, 117, 30, 80, 86, 115, 103, 115, 64, 112, 61, 133, 156, 161, 253, 25, 225, 34
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32mf2_t out = __riscv_vsub_vx_i32mf2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
  }
   int golden[] = {
   164, 22, -69, 48, -7, 23, 130, 6, 185, 2, -11, 70, -25, -78, -197, 149, -125, 94, -52, 1, 180, 37, 54, -247, 138, -51, -117, 32, 158, -183, -153, -137, -69, 63, 140, -84, -40, 138, -71, 204, 24, -100, 32, -124, -134, 83, -38, 30, 23, 115, -41, 83, -16, -35, 184, 141, 19, 113, 81, 61, -29, 200, -92, 184
   };
    int fail = 0;
    for (int i = 0; i < 64; i++)
        if (golden0[i] != out0_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden0[i], out0[i]);
            fail++;
            }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
