/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m4_t data1[] = {
    4983, 11280, 10038, 14576, 29564, 23677, 19059, 33605, 45039, 9239, 61236, 58010, 29318, 16399, 24861, 6370, 49397, 21103, 55022, 1720, 15710, 40006, 2260, 23779, 20055, 21967, 10283, 36584, 15376, 47784, 35967, 57690
    };
    const vint16m4_t *in1 = &data1[0];
    vint16m4_t data2[] = {
    23442, 2609, 22777, 20654, 52733, 52092, 41971, 1983, 47195, 19590, 2468, 50256, 59680, 1837, 13253, 65328, 25791, 265, 43978, 40364, 35759, 62165, 26386, 21569, 12206, 57866, 43123, 55929, 42941, 23486, 18378, 5289
    };
    const vint16m4_t *in2 = &data2[0];
    vint16m4_t out_data[] = {
    6271, 52597, 33433, 30646, 14061, 38131, 41726, 21077, 64444, 15833, 32281, 23594, 56336, 1349, 29879, 47806, 10728, 38672, 11278, 20413, 5837, 20850, 62080, 63810, 59450, 29696, 26373, 23955, 25215, 46104, 3757, 22354
    };
    vint16m4_t *out = &out_data[0];
    int masked[] = {
    1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 32, Q_element = 16;n >= 0; n -= Q_element) {
        vint16m4_t out = __riscv_vadd_vv_i16m4_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint16m4_t golden[] = {
    28425, 13889, 33433, 35230, 82297, 38131, 41726, 21077, 92234, 28829, 63704, 23594, 56336, 18236, 29879, 71698, 75188, 38672, 99000, 20413, 5837, 20850, 28646, 45348, 32261, 29696, 53406, 92513, 25215, 71270, 3757, 22354
    };
    int fail = 0;
    for (int i = 0; i < 32; i++){
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
}
