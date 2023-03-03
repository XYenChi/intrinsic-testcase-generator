/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    46776, 49499, 62014, 13301, 59980, 21548, 23076, 7820, 35026, 4556, 10139, 1522, 44874, 46793, 42257, 54148
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    58205, 36264, 61932, 19711, 43295, 8149, 22261, 40584, 22259, 40328, 63366, 11698, 36668, 32754, 30941, 50457
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    35375, 62635, 6556, 44274, 51357, 21688, 52858, 38020, 21594, 50325, 25547, 16831, 34256, 58851, 6153, 51354
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -11429, 13235, 82, -6410, 16685, 13398, 815, -32764, 12766, -35773, -53228, -10176, 8205, 14038, 11315, 3690
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
