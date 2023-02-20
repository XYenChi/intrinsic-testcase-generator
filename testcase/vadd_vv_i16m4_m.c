/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m4_t data1[] = {
    84, 255, 158, 215, 93, 237, 117, 248, 115, 153, 25, 93, 17, 147, 67, 105, 103, 64, 98, 27, 20, 144, 99, 248, 54, 86, 138, 189, 98, 117, 79, 74, 200, 47, 178, 133, 20, 179, 169, 239, 149, 196, 175, 122, 134, 31, 163, 1, 193, 20, 170, 123, 226, 16, 67, 178, 113, 232, 83, 12, 59, 114, 41, 98
    };
    const vint16m4_t *in1 = &data1[0];
    vint16m4_t data2[] = {
    23, 94, 96, 104, 234, 13, 168, 93, 72, 148, 89, 221, 142, 153, 65, 174, 71, 191, 73, 222, 193, 7, 186, 195, 89, 2, 19, 254, 66, 10, 211, 10, 111, 92, 4, 58, 164, 40, 81, 205, 16, 67, 74, 103, 108, 127, 24, 250, 106, 128, 20, 175, 129, 23, 196, 225, 127, 242, 94, 146, 233, 39, 41, 36
    };
    const vint16m4_t *in2 = &data2[0];
    vint16m4_t out_data[] = {
    134, 95, 103, 140, 249, 132, 58, 127, 128, 195, 0, 198, 29, 174, 103, 86, 190, 112, 212, 98, 246, 40, 59, 21, 151, 115, 58, 59, 164, 105, 153, 170, 83, 177, 219, 233, 35, 4, 156, 13, 131, 208, 67, 31, 149, 45, 7, 59, 122, 40, 62, 212, 206, 140, 94, 50, 33, 128, 54, 10, 219, 73, 89, 230
    };
    vint16m4_t *out = &out_data[0];
    int masked[] = {
    0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m4_t out = __riscv_vadd_vv_i16m4_m (, mask, data1, data264);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint16m4_t golden[] = {
    134, 95, 254, 140, 249, 250, 58, 341, 187, 301, 114, 314, 159, 300, 103, 86, 190, 255, 212, 98, 246, 40, 59, 443, 151, 115, 58, 443, 164, 105, 290, 170, 311, 177, 219, 233, 35, 4, 250, 13, 165, 263, 67, 225, 242, 45, 187, 59, 122, 40, 62, 298, 206, 39, 263, 403, 240, 474, 177, 10, 219, 153, 89, 134
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
