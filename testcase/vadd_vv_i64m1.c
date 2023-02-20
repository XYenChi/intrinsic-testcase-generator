/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m1_t data1[] = {
    60, 60, 112, 161, 136, 16, 71, 161, 137, 27, 184, 131, 147, 219, 234, 205, 185, 26, 113, 218, 97, 126, 41, 197, 181, 198, 187, 243, 236, 172, 48, 106, 249, 197, 199, 75, 145, 146, 36, 169, 247, 206, 177, 30, 5, 139, 112, 73, 195, 41, 62, 199, 205, 104, 198, 9, 231, 50, 30, 207, 210, 251, 239, 178
    };
    const vint64m1_t *in1 = &data1[0];
    vint64m1_t data2[] = {
    236, 231, 47, 246, 26, 206, 38, 107, 229, 214, 50, 60, 122, 229, 35, 169, 77, 98, 195, 250, 25, 112, 18, 192, 30, 131, 59, 168, 239, 177, 138, 190, 36, 99, 249, 220, 116, 178, 117, 29, 37, 213, 88, 177, 76, 52, 59, 192, 41, 216, 198, 0, 196, 190, 150, 64, 41, 56, 25, 239, 88, 172, 3, 183
    };
    const vint64m1_t *in2 = &data2[0];
    vint64m1_t out_data[64];
    vint64m1_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint64m1_t out = __riscv_vadd_vv_i64m1 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint64m1_t golden[] = {
    296, 291, 159, 407, 162, 222, 109, 268, 366, 241, 234, 191, 269, 448, 269, 374, 262, 124, 308, 468, 122, 238, 59, 389, 211, 329, 246, 411, 475, 349, 186, 296, 285, 296, 448, 295, 261, 324, 153, 198, 284, 419, 265, 207, 81, 191, 171, 265, 236, 257, 260, 199, 401, 294, 348, 73, 272, 106, 55, 446, 298, 423, 242, 361
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
