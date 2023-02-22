/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m8_t data1[] = {
    12, 65, 64, 126, 235, 91, 105, 116, 16, 102, 145, 89, 97, 251, 18, 211, 5, 123, 18, 133, 197, 111, 192, 208, 28, 78, 129, 41, 101, 76, 175, 210, 170, 34, 84, 169, 13, 151, 154, 227, 170, 208, 43, 168, 166, 133, 187, 73, 63, 98, 234, 210, 96, 239, 151, 75, 87, 36, 213, 66, 165, 3, 242, 220
    };
    const vint32m8_t *in1 = &data1[0];
    vint32m8_t data2[] = {
    52, 206, 94, 38, 22, 128, 55, 3, 254, 40, 88, 142, 245, 239, 250, 156, 137, 125, 108, 184, 211, 118, 19, 180, 204, 91, 72, 69, 118, 96, 68, 8, 189, 194, 24, 24, 15, 42, 115, 219, 121, 168, 64, 144, 242, 105, 176, 188, 241, 44, 101, 13, 76, 158, 105, 222, 94, 200, 195, 167, 20, 131, 70, 227
    };
    const vint32m8_t *in2 = &data2[0];
    vint32m8_t out_data[64];
    vint32m8_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32m8_t out = __riscv_vadd_vx_i32m8 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32m8_t golden[] = {
    64, 271, 158, 164, 257, 219, 160, 119, 270, 142, 233, 231, 342, 490, 268, 367, 142, 248, 126, 317, 408, 229, 211, 388, 232, 169, 201, 110, 219, 172, 243, 218, 359, 228, 108, 193, 28, 193, 269, 446, 291, 376, 107, 312, 408, 238, 363, 261, 304, 142, 335, 223, 172, 397, 256, 297, 181, 236, 408, 233, 185, 134, 312, 447
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