/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    29982, 33649, 25875, 31399, 25106, 45592, 43109, 1556, 22929, 63944, 35648, 33768, 43895, 49322, 64668, 60125
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    31340, 64243, 52805, 11885, 25584, 14453, 28312, 65009, 23861, 49902, 7071, 40629, 22061, 37658, 37395, 57362
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    40147, 3932, 39601, 2898, 25560, 6044, 30666, 956, 40809, 20620, 65365, 54816, 1268, 53128, 48629, 10637
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -1358, -30594, -26931, 19514, -478, 31138, 14797, -63454, -933, 14041, 28577, -6861, 21834, 11663, 27272, 2762
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
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
