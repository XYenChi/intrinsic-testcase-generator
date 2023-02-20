/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m8_t data1[] = {
    233, 218, 221, 186, 227, 41, 158, 136, 239, 105, 50, 180, 152, 54, 90, 233, 218, 206, 91, 132, 145, 230, 96, 248, 144, 0, 56, 101, 109, 119, 230, 98, 69, 104, 246, 211, 71, 186, 122, 170, 108, 204, 80, 212, 182, 139, 17, 78, 225, 208, 95, 54, 214, 245, 154, 180, 18, 170, 248, 70, 66, 192, 0, 145
    };
    const vint64m8_t *in1 = &data1[0];
    vint64m8_t data2[] = {
    46, 140, 63, 116, 245, 189, 165, 249, 150, 189, 43, 25, 255, 7, 189, 225, 99, 133, 237, 84, 206, 148, 145, 197, 127, 81, 161, 254, 72, 21, 150, 47, 163, 43, 86, 226, 229, 27, 170, 56, 228, 170, 105, 5, 2, 75, 10, 89, 26, 249, 235, 195, 206, 4, 237, 54, 213, 215, 137, 113, 10, 245, 247, 53
    };
    const vint64m8_t *in2 = &data2[0];
    vint64m8_t out_data[64];
    vint64m8_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint64m8_t out = __riscv_vadd_vv_i64m8 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint64m8_t golden[] = {
    279, 358, 284, 302, 472, 230, 323, 385, 389, 294, 93, 205, 407, 61, 279, 458, 317, 339, 328, 216, 351, 378, 241, 445, 271, 81, 217, 355, 181, 140, 380, 145, 232, 147, 332, 437, 300, 213, 292, 226, 336, 374, 185, 217, 184, 214, 27, 167, 251, 457, 330, 249, 420, 249, 391, 234, 231, 385, 385, 183, 76, 437, 247, 198
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
