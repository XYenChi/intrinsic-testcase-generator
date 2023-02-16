/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    int data1[] = {
    181, 155, 38, 152, 47, 90, 174, 79, 117, 225, 210, 18, 159, 160, 240, 209, 135, 116, 227, 58, 107, 55, 18, 63, 50, 105, 196, 220, 71, 56, 252, 67, 160, 55, 105, 94, 113, 63, 203, 112, 89, 45, 93, 246, 194, 57, 127, 7, 54, 13, 21, 227, 75, 52, 109, 104, 52, 231, 52, 227, 104, 127, 89, 71
    };
    const int *in1 = &data1[0];
    int data2[] = {
    57, 154, 85, 136, 176, 169, 234, 224, 200, 20, 238, 113, 231, 132, 139, 134, 199, 39, 245, 3, 186, 71, 234, 215, 27, 193, 168, 33, 226, 58, 158, 181, 69, 172, 192, 55, 103, 153, 149, 190, 142, 77, 28, 199, 117, 142, 197, 128, 83, 86, 192, 31, 140, 54, 143, 116, 226, 188, 185, 216, 241, 77, 80, 215
    };
    const int *in2 = &data2[0];
    int out_data[64];
    int *out = &out_data[0];
    int masked[] = {
    0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32m4_t out = __riscv_vsub_vv_i32m4_m (mask, data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
   int golden[] = {
   124, 1, -47, 16, -129, -79, -60, -145, -83, 205, -28, -95, -72, 28, 101, 75, -64, 77, -18, 55, -79, -16, -216, -152, 23, -88, 28, 187, -155, -2, 94, -114, 91, -117, -87, 39, 10, -90, 54, -78, -53, -32, 65, 47, 77, -85, -70, -121, -29, -73, -171, 196, -65, -2, -34, -12, -174, 43, -133, 11, -137, 50, 9, -144
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
