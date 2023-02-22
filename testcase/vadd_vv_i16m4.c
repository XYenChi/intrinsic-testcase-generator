/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m4_t data1[] = {
    19388, 8531, 50928, 24211, 1908, 65412, 34930, 5433, 45668, 40843, 20236, 17152, 615, 29754, 18144, 31180, 55298, 19027, 62677, 20664, 8824, 23178, 13647, 27323, 53958, 57446, 59563, 18612, 63619, 37798, 46640, 23985
    };
    const vint16m4_t *in1 = &data1[0];
    vint16m4_t data2[] = {
    36625, 31705, 39944, 38852, 42576, 26203, 19937, 57747, 4276, 51508, 24350, 47821, 2324, 33963, 9975, 57298, 56065, 2730, 18836, 43360, 49930, 19886, 54699, 11676, 18410, 31086, 32657, 17979, 21924, 25147, 29102, 48302
    };
    const vint16m4_t *in2 = &data2[0];
    vint16m4_t out_data[64];
    vint16m4_t *out = &out_data[0];
    for (int n = 32, Q_element = 16;n >= 0; n -= Q_element) {
        vint16m4_t out = __riscv_vadd_vv_i16m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16m4_t golden[] = {
    56013, 40236, 90872, 63063, 44484, 91615, 54867, 63180, 49944, 92351, 44586, 64973, 2939, 63717, 28119, 88478, 111363, 21757, 81513, 64024, 58754, 43064, 68346, 38999, 72368, 88532, 92220, 36591, 85543, 62945, 75742, 72287
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
