/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m1_t data1[] = {
    141, 53, 141, 84, 190, 171, 60, 184, 78, 47, 16, 237, 219, 155, 89, 126, 143, 168, 117, 5, 33, 148, 38, 239, 62, 35, 122, 142, 226, 168, 151, 94, 44, 77, 198, 90, 141, 51, 24, 191, 59, 166, 121, 68, 138, 205, 34, 117, 171, 38, 211, 243, 11, 168, 67, 224, 51, 129, 149, 221, 212, 55, 33, 55
    };
    const vint16m1_t *in1 = &data1[0];
    vint16m1_t data2[] = {
    0, 106, 11, 62, 3, 251, 43, 88, 113, 23, 131, 190, 205, 108, 25, 73, 211, 162, 149, 158, 233, 85, 79, 22, 214, 33, 168, 156, 158, 205, 3, 71, 47, 177, 237, 110, 253, 10, 113, 75, 138, 82, 79, 78, 11, 241, 152, 183, 57, 178, 91, 59, 80, 252, 93, 59, 109, 121, 83, 247, 72, 160, 180, 234
    };
    const vint16m1_t *in2 = &data2[0];
    vint16m1_t out_data[64];
    vint16m1_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m1_t out = __riscv_vadd_vx_i16m1 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16m1_t golden[] = {
    141, 159, 152, 146, 193, 422, 103, 272, 191, 70, 147, 427, 424, 263, 114, 199, 354, 330, 266, 163, 266, 233, 117, 261, 276, 68, 290, 298, 384, 373, 154, 165, 91, 254, 435, 200, 394, 61, 137, 266, 197, 248, 200, 146, 149, 446, 186, 300, 228, 216, 302, 302, 91, 420, 160, 283, 160, 250, 232, 468, 284, 215, 213, 289
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
