/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf2_t data1[] = {
    61, 159, 144, 20, 101, 129, 174, 244, 242, 173, 86, 104, 184, 50, 67, 180, 108, 158, 157, 118, 35, 240, 90, 47, 93, 14, 120, 148, 97, 113, 101, 151, 206, 80, 84, 55, 148, 218, 93, 243, 78, 225, 195, 89, 183, 21, 202, 156, 153, 130, 0, 169, 53, 72, 151, 176, 217, 62, 251, 140, 200, 245, 168, 52
    };
    const vint8mf2_t *in1 = &data1[0];
    vint8mf2_t data2[] = {
    24, 42, 38, 163, 20, 220, 172, 196, 80, 44, 1, 45, 128, 215, 244, 1, 31, 241, 195, 41, 231, 115, 17, 65, 120, 90, 244, 186, 248, 134, 42, 63, 95, 39, 74, 127, 215, 175, 117, 211, 21, 253, 203, 98, 42, 153, 44, 83, 238, 124, 148, 14, 100, 162, 112, 32, 33, 232, 56, 212, 48, 8, 149, 11
    };
    const vint8mf2_t *in2 = &data2[0];
    vint8mf2_t out_data[64];
    vint8mf2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf2_t out = __riscv_vadd_vv_i8mf2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf2_t golden[] = {
    85, 201, 182, 183, 121, 349, 346, 440, 322, 217, 87, 149, 312, 265, 311, 181, 139, 399, 352, 159, 266, 355, 107, 112, 213, 104, 364, 334, 345, 247, 143, 214, 301, 119, 158, 182, 363, 393, 210, 454, 99, 478, 398, 187, 225, 174, 246, 239, 391, 254, 148, 183, 153, 234, 263, 208, 250, 294, 307, 352, 248, 253, 317, 63
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
