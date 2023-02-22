/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m4_t data1[] = {
    35406, 16834, 24049, 36123, 3119, 31912, 50216, 37573, 37711, 35104, 35570, 24290, 42759, 5774, 29020, 27592, 51004, 33378, 12894, 25167, 9650, 59254, 20032, 58925, 63919, 13735, 18824, 2231, 5620, 55282, 9527, 32937
    };
    const vint16m4_t *in1 = &data1[0];
    vint16m4_t data2[] = {
    17292, 28021, 56755, 33111, 28175, 63957, 33502, 40621, 50717, 30880, 18478, 62923, 64044, 61680, 1912, 19555, 42782, 13576, 34349, 34979, 1817, 13453, 41269, 3335, 36676, 36118, 33508, 2440, 29998, 49372, 44198, 34859
    };
    const vint16m4_t *in2 = &data2[0];
    vint16m4_t out_data[64];
    vint16m4_t *out = &out_data[0];
    for (int n = 32, Q_element = 16;n >= 0; n -= Q_element) {
        vint16m4_t out = __riscv_vadd_vx_i16m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16m4_t golden[] = {
    52698, 44855, 80804, 69234, 31294, 95869, 83718, 78194, 88428, 65984, 54048, 87213, 106803, 67454, 30932, 47147, 93786, 46954, 47243, 60146, 11467, 72707, 61301, 62260, 100595, 49853, 52332, 4671, 35618, 104654, 53725, 67796
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
