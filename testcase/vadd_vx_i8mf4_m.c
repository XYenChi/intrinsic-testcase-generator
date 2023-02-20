/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf4_t data1[] = {
    154, 145, 37, 42, 98, 195, 24, 196, 203, 118, 68, 250, 72, 162, 129, 143, 130, 82, 211, 167, 203, 214, 125, 207, 187, 177, 122, 146, 16, 193, 43, 37, 1, 232, 99, 74, 252, 69, 44, 25, 27, 156, 122, 19, 174, 168, 207, 167, 194, 58, 138, 178, 205, 43, 207, 186, 220, 62, 157, 48, 112, 172, 233, 13
    };
    const vint8mf4_t *in1 = &data1[0];
    vint8mf4_t data2[] = {
    203, 22, 240, 3, 87, 45, 229, 232, 45, 28, 29, 139, 81, 127, 76, 56, 178, 92, 31, 159, 97, 149, 67, 218, 190, 58, 214, 8, 0, 114, 73, 178, 248, 162, 198, 226, 174, 213, 193, 3, 251, 52, 22, 20, 137, 205, 252, 15, 220, 217, 46, 226, 163, 12, 219, 68, 116, 89, 29, 207, 123, 238, 75, 106
    };
    const vint8mf4_t *in2 = &data2[0];
    vint8mf4_t out_data[] = {
    183, 136, 138, 185, 247, 172, 74, 14, 81, 92, 13, 134, 244, 96, 177, 238, 113, 211, 27, 251, 247, 42, 15, 24, 108, 147, 155, 201, 64, 177, 191, 140, 101, 124, 191, 187, 150, 113, 140, 174, 1, 129, 4, 179, 211, 141, 157, 108, 93, 208, 203, 113, 181, 130, 130, 147, 252, 94, 82, 144, 21, 147, 232, 13
    };
    vint8mf4_t *out = &out_data[0];
    int masked[] = {
    0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf4_t out = __riscv_vadd_vx_i8mf4_m (, mask, data1, data264);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint8mf4_t golden[] = {
    183, 136, 138, 45, 247, 172, 253, 428, 248, 146, 97, 134, 153, 96, 177, 238, 113, 211, 27, 251, 300, 42, 15, 24, 377, 147, 336, 154, 64, 177, 116, 215, 101, 124, 297, 187, 150, 282, 237, 28, 1, 129, 144, 39, 311, 141, 157, 182, 93, 208, 184, 404, 181, 130, 426, 254, 252, 151, 82, 255, 21, 147, 232, 13
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
