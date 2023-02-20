/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m4_t data1[] = {
    35, 165, 29, 7, 159, 8, 179, 251, 130, 186, 38, 38, 46, 238, 43, 181, 247, 9, 120, 210, 161, 144, 0, 81, 30, 230, 116, 70, 35, 34, 154, 101, 194, 194, 65, 232, 248, 150, 160, 144, 218, 236, 44, 246, 108, 229, 117, 62, 36, 244, 73, 2, 35, 211, 173, 250, 35, 141, 44, 92, 247, 215, 146, 249
    };
    const vint8m4_t *in1 = &data1[0];
    vint8m4_t data2[] = {
    30, 231, 206, 131, 119, 36, 133, 133, 207, 98, 210, 169, 199, 31, 231, 86, 238, 243, 3, 188, 80, 10, 5, 93, 42, 222, 206, 230, 194, 73, 158, 59, 21, 226, 253, 191, 141, 136, 98, 171, 61, 155, 162, 191, 57, 106, 238, 161, 206, 233, 248, 226, 151, 157, 170, 167, 55, 10, 23, 84, 247, 43, 23, 211
    };
    const vint8m4_t *in2 = &data2[0];
    vint8m4_t out_data[64];
    vint8m4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m4_t out = __riscv_vadd_vv_i8m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m4_t golden[] = {
    65, 396, 235, 138, 278, 44, 312, 384, 337, 284, 248, 207, 245, 269, 274, 267, 485, 252, 123, 398, 241, 154, 5, 174, 72, 452, 322, 300, 229, 107, 312, 160, 215, 420, 318, 423, 389, 286, 258, 315, 279, 391, 206, 437, 165, 335, 355, 223, 242, 477, 321, 228, 186, 368, 343, 417, 90, 151, 67, 176, 494, 258, 169, 460
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
