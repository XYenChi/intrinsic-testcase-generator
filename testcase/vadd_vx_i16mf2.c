/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16mf2_t data1[] = {
    59, 170, 22, 131, 170, 230, 245, 92, 56, 249, 222, 26, 80, 55, 41, 38, 213, 16, 126, 189, 202, 60, 169, 89, 157, 76, 197, 59, 117, 191, 174, 57, 54, 235, 88, 96, 207, 164, 40, 141, 188, 180, 83, 193, 233, 120, 106, 192, 179, 215, 67, 55, 93, 188, 38, 144, 238, 147, 23, 124, 18, 50, 130, 16
    };
    const vint16mf2_t *in1 = &data1[0];
    vint16mf2_t data2[] = {
    243, 248, 110, 210, 60, 82, 115, 60, 138, 229, 221, 116, 161, 88, 60, 135, 243, 243, 13, 21, 201, 236, 15, 50, 146, 83, 190, 223, 72, 93, 148, 249, 231, 225, 162, 100, 185, 41, 179, 239, 98, 239, 247, 225, 108, 180, 253, 22, 176, 147, 3, 41, 154, 128, 44, 168, 162, 162, 148, 254, 228, 31, 152, 244
    };
    const vint16mf2_t *in2 = &data2[0];
    vint16mf2_t out_data[64];
    vint16mf2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16mf2_t out = __riscv_vadd_vx_i16mf2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16mf2_t golden[] = {
    302, 418, 132, 341, 230, 312, 360, 152, 194, 478, 443, 142, 241, 143, 101, 173, 456, 259, 139, 210, 403, 296, 184, 139, 303, 159, 387, 282, 189, 284, 322, 306, 285, 460, 250, 196, 392, 205, 219, 380, 286, 419, 330, 418, 341, 300, 359, 214, 355, 362, 70, 96, 247, 316, 82, 312, 400, 309, 171, 378, 246, 81, 282, 260
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
