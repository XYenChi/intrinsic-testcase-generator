/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m2_t data1[] = {
    163, 76, 134, 6, 183, 217, 138, 187, 78, 104, 53, 224, 29, 33, 107, 179, 233, 126, 75, 123, 83, 103, 97, 157, 130, 212, 132, 151, 36, 246, 72, 204, 184, 39, 253, 196, 56, 116, 210, 34, 234, 60, 13, 207, 225, 248, 210, 240, 21, 133, 127, 91, 54, 232, 180, 31, 251, 195, 146, 99, 34, 42, 98, 237
    };
    const vint16m2_t *in1 = &data1[0];
    vint16m2_t data2[] = {
    243, 20, 222, 205, 106, 56, 253, 37, 39, 156, 80, 158, 164, 165, 49, 156, 127, 151, 186, 163, 173, 195, 49, 165, 102, 105, 134, 13, 7, 146, 99, 104, 50, 168, 169, 27, 70, 109, 209, 146, 92, 36, 17, 94, 183, 53, 192, 15, 112, 161, 135, 156, 142, 53, 88, 220, 12, 117, 128, 184, 7, 26, 64, 164
    };
    const vint16m2_t *in2 = &data2[0];
    vint16m2_t out_data[] = {
    94, 147, 140, 251, 80, 205, 112, 66, 145, 36, 198, 142, 226, 56, 180, 149, 251, 129, 152, 174, 113, 8, 160, 131, 207, 55, 222, 233, 231, 98, 63, 78, 62, 89, 173, 244, 200, 147, 33, 184, 97, 129, 109, 29, 211, 187, 72, 54, 76, 127, 248, 102, 15, 210, 22, 226, 82, 121, 17, 36, 116, 21, 93, 206
    };
    vint16m2_t *out = &out_data[0];
    int masked[] = {
    1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m2_t out = __riscv_vadd_vx_i16m2_m (, mask, data1, data264);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint16m2_t golden[] = {
    406, 96, 356, 251, 289, 205, 112, 224, 117, 36, 198, 142, 193, 56, 180, 149, 360, 129, 261, 286, 256, 8, 160, 131, 207, 55, 222, 233, 231, 98, 63, 308, 234, 207, 173, 223, 126, 225, 33, 184, 326, 96, 109, 301, 211, 301, 72, 255, 133, 294, 248, 247, 196, 210, 268, 251, 82, 121, 274, 283, 41, 68, 162, 401
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
