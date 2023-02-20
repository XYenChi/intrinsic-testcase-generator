/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m4_t data1[] = {
    254, 151, 101, 163, 243, 194, 178, 107, 24, 79, 171, 183, 245, 155, 14, 92, 148, 8, 1, 81, 42, 198, 147, 213, 115, 237, 225, 209, 159, 99, 143, 174, 46, 180, 149, 148, 82, 157, 119, 241, 38, 116, 19, 30, 45, 69, 112, 198, 76, 6, 173, 55, 154, 34, 168, 183, 50, 57, 124, 140, 125, 171, 54, 207
    };
    const vint32m4_t *in1 = &data1[0];
    vint32m4_t data2[] = {
    134, 43, 229, 186, 68, 194, 253, 147, 218, 212, 16, 113, 218, 55, 95, 253, 72, 36, 219, 240, 245, 189, 77, 71, 68, 2, 154, 92, 145, 22, 206, 131, 9, 227, 22, 8, 203, 158, 187, 19, 172, 47, 149, 24, 62, 2, 12, 137, 220, 169, 249, 14, 144, 7, 100, 2, 64, 185, 55, 154, 130, 77, 189, 79
    };
    const vint32m4_t *in2 = &data2[0];
    vint32m4_t out_data[64];
    vint32m4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32m4_t out = __riscv_vadd_vv_i32m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32m4_t golden[] = {
    388, 194, 330, 349, 311, 388, 431, 254, 242, 291, 187, 296, 463, 210, 109, 345, 220, 44, 220, 321, 287, 387, 224, 284, 183, 239, 379, 301, 304, 121, 349, 305, 55, 407, 171, 156, 285, 315, 306, 260, 210, 163, 168, 54, 107, 71, 124, 335, 296, 175, 422, 69, 298, 41, 268, 185, 114, 242, 179, 294, 255, 248, 243, 286
    };
    int fail = 0;
    for (int i = 0; i < 64; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
