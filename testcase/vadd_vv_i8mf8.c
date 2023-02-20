/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf8_t data1[] = {
    245, 231, 31, 227, 178, 21, 225, 69, 75, 1, 23, 252, 41, 28, 191, 195, 245, 9, 94, 117, 153, 21, 200, 122, 98, 222, 130, 165, 178, 137, 172, 173, 114, 79, 107, 152, 131, 51, 72, 98, 73, 157, 231, 176, 167, 251, 167, 206, 197, 12, 10, 242, 19, 181, 26, 39, 145, 181, 12, 247, 166, 68, 31, 23
    };
    const vint8mf8_t *in1 = &data1[0];
    vint8mf8_t data2[] = {
    52, 152, 53, 9, 143, 238, 240, 97, 143, 189, 181, 15, 92, 156, 215, 198, 1, 47, 38, 78, 57, 135, 230, 43, 57, 59, 32, 15, 90, 155, 144, 139, 10, 33, 253, 179, 153, 131, 38, 31, 146, 48, 12, 180, 126, 32, 226, 91, 199, 172, 236, 23, 88, 14, 28, 59, 44, 120, 72, 11, 162, 71, 233, 13
    };
    const vint8mf8_t *in2 = &data2[0];
    vint8mf8_t out_data[64];
    vint8mf8_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf8_t out = __riscv_vadd_vv_i8mf8 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf8_t golden[] = {
    297, 383, 84, 236, 321, 259, 465, 166, 218, 190, 204, 267, 133, 184, 406, 393, 246, 56, 132, 195, 210, 156, 430, 165, 155, 281, 162, 180, 268, 292, 316, 312, 124, 112, 360, 331, 284, 182, 110, 129, 219, 205, 243, 356, 293, 283, 393, 297, 396, 184, 246, 265, 107, 195, 54, 98, 189, 301, 84, 258, 328, 139, 264, 36
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
