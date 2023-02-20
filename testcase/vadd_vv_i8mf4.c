/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf4_t data1[] = {
    26, 221, 101, 134, 216, 25, 41, 88, 252, 184, 166, 132, 186, 176, 132, 103, 196, 193, 66, 165, 132, 111, 135, 88, 25, 8, 174, 113, 165, 117, 188, 253, 47, 65, 114, 247, 89, 122, 170, 84, 35, 196, 31, 152, 247, 95, 130, 123, 243, 62, 229, 73, 106, 71, 134, 18, 178, 253, 107, 7, 216, 179, 173, 107
    };
    const vint8mf4_t *in1 = &data1[0];
    vint8mf4_t data2[] = {
    186, 111, 233, 34, 34, 38, 20, 197, 145, 13, 42, 80, 145, 93, 25, 77, 173, 53, 205, 245, 214, 6, 55, 67, 100, 16, 161, 166, 33, 38, 156, 88, 181, 136, 157, 43, 38, 15, 51, 243, 176, 37, 76, 129, 104, 227, 25, 174, 167, 83, 228, 102, 176, 114, 238, 156, 227, 157, 85, 223, 211, 50, 132, 177
    };
    const vint8mf4_t *in2 = &data2[0];
    vint8mf4_t out_data[64];
    vint8mf4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf4_t out = __riscv_vadd_vv_i8mf4 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf4_t golden[] = {
    212, 332, 334, 168, 250, 63, 61, 285, 397, 197, 208, 212, 331, 269, 157, 180, 369, 246, 271, 410, 346, 117, 190, 155, 125, 24, 335, 279, 198, 155, 344, 341, 228, 201, 271, 290, 127, 137, 221, 327, 211, 233, 107, 281, 351, 322, 155, 297, 410, 145, 457, 175, 282, 185, 372, 174, 405, 410, 192, 230, 427, 229, 305, 284
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
