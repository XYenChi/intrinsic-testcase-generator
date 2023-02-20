/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16mf4_t data1[] = {
    249, 216, 139, 7, 112, 250, 249, 194, 50, 103, 1, 5, 31, 121, 84, 29, 177, 69, 215, 47, 24, 246, 125, 144, 100, 26, 165, 1, 48, 142, 3, 193, 78, 128, 199, 194, 134, 48, 202, 227, 28, 100, 133, 45, 123, 82, 248, 135, 120, 43, 216, 66, 113, 163, 250, 49, 111, 165, 133, 148, 77, 78, 43, 243
    };
    const vint16mf4_t *in1 = &data1[0];
    vint16mf4_t data2[] = {
    38, 181, 5, 4, 45, 32, 252, 40, 208, 194, 191, 1, 206, 67, 233, 16, 212, 95, 230, 249, 150, 74, 65, 177, 44, 24, 245, 21, 90, 151, 90, 171, 35, 203, 208, 112, 136, 241, 116, 140, 99, 116, 245, 172, 154, 26, 70, 154, 177, 190, 248, 43, 219, 136, 113, 185, 91, 250, 117, 169, 188, 141, 50, 55
    };
    const vint16mf4_t *in2 = &data2[0];
    vint16mf4_t out_data[64];
    vint16mf4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16mf4_t out = __riscv_vadd_vv_i16mf4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16mf4_t golden[] = {
    287, 397, 144, 11, 157, 282, 501, 234, 258, 297, 192, 6, 237, 188, 317, 45, 389, 164, 445, 296, 174, 320, 190, 321, 144, 50, 410, 22, 138, 293, 93, 364, 113, 331, 407, 306, 270, 289, 318, 367, 127, 216, 378, 217, 277, 108, 318, 289, 297, 233, 464, 109, 332, 299, 363, 234, 202, 415, 250, 317, 265, 219, 93, 298
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
