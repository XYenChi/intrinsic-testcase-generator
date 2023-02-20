/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m2_t data1[] = {
    118, 28, 221, 134, 59, 183, 237, 66, 133, 137, 44, 51, 54, 32, 131, 245, 240, 63, 136, 156, 27, 189, 68, 53, 215, 42, 31, 192, 247, 118, 94, 184, 102, 24, 39, 204, 91, 205, 57, 49, 19, 10, 175, 200, 150, 224, 177, 150, 234, 183, 17, 82, 55, 66, 19, 31, 109, 86, 55, 98, 107, 172, 180, 209
    };
    const vint32m2_t *in1 = &data1[0];
    vint32m2_t data2[] = {
    246, 172, 186, 47, 243, 140, 228, 59, 82, 195, 112, 234, 7, 6, 78, 131, 200, 194, 236, 108, 15, 47, 2, 166, 108, 90, 144, 52, 46, 105, 243, 222, 2, 18, 213, 175, 111, 146, 66, 161, 246, 55, 3, 30, 67, 119, 119, 12, 99, 104, 113, 220, 209, 23, 101, 23, 215, 142, 72, 163, 19, 70, 129, 40
    };
    const vint32m2_t *in2 = &data2[0];
    vint32m2_t out_data[64];
    vint32m2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32m2_t out = __riscv_vadd_vv_i32m2 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32m2_t golden[] = {
    364, 200, 407, 181, 302, 323, 465, 125, 215, 332, 156, 285, 61, 38, 209, 376, 440, 257, 372, 264, 42, 236, 70, 219, 323, 132, 175, 244, 293, 223, 337, 406, 104, 42, 252, 379, 202, 351, 123, 210, 265, 65, 178, 230, 217, 343, 296, 162, 333, 287, 130, 302, 264, 89, 120, 54, 324, 228, 127, 261, 126, 242, 309, 249
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
