/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m2_t data1[] = {
    93, 130, 168, 151, 8, 65, 79, 124, 246, 193, 170, 66, 218, 161, 104, 198, 219, 102, 238, 39, 46, 216, 46, 60, 74, 167, 252, 61, 80, 93, 42, 160, 41, 84, 52, 8, 151, 18, 211, 104, 19, 173, 121, 45, 26, 10, 133, 119, 209, 24, 11, 161, 222, 211, 94, 173, 249, 94, 62, 198, 123, 76, 129, 122
    };
    const vint64m2_t *in1 = &data1[0];
    vint64m2_t data2[] = {
    75, 102, 99, 79, 242, 208, 217, 201, 149, 118, 204, 149, 140, 120, 187, 16, 255, 186, 61, 248, 45, 124, 149, 51, 21, 19, 114, 11, 96, 57, 93, 213, 21, 197, 90, 68, 52, 217, 220, 226, 170, 174, 58, 247, 145, 7, 145, 186, 145, 32, 28, 92, 141, 206, 17, 65, 112, 119, 150, 12, 175, 110, 122, 88
    };
    const vint64m2_t *in2 = &data2[0];
    vint64m2_t out_data[64];
    vint64m2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint64m2_t out = __riscv_vadd_vv_i64m2 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint64m2_t golden[] = {
    168, 232, 267, 230, 250, 273, 296, 325, 395, 311, 374, 215, 358, 281, 291, 214, 474, 288, 299, 287, 91, 340, 195, 111, 95, 186, 366, 72, 176, 150, 135, 373, 62, 281, 142, 76, 203, 235, 431, 330, 189, 347, 179, 292, 171, 17, 278, 305, 354, 56, 39, 253, 363, 417, 111, 238, 361, 213, 212, 210, 298, 186, 251, 210
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
