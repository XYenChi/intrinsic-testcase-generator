/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    32534, 39504, 54980, 7579, 49616, 49482, 1719, 49962, 52542, 61344, 3795, 62203, 20658, 32924, 20261, 65185
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    10482, 30431, 4186, 34588, 24007, 34809, 31535, 61558, 45699, 15130, 34206, 6791, 54081, 41707, 35418, 60342
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    4131, 63034, 33628, 30453, 57603, 47781, 21274, 65468, 29725, 40473, 50810, 8162, 49956, 33686, 13433, 18303
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    22052, 9073, 50793, -27010, 25609, 14673, -29817, -11596, 6843, 46214, -30412, 55411, -33423, -8783, -15157, 4843
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
