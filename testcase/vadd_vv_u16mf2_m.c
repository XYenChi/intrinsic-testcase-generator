/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -28668, 19652, -7964, 20681, -20590, 26238, 13616, -9689, 24512, -14240, -15062, 10961, -2634, -653, -11214, 23865
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -30863, 11326, 23793, -3653, 20614, -21577, -22709, -24782, -17470, 13780, 20416, 25581, -5305, -24088, 31417, 21787
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const int out_data[] = {
    -12734, 7110, 25586, 23636, -22583, 17937, -11561, 15694, 4308, -3401, 18396, 16502, -10315, -24958, 1591, 18156
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u16mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf2 (bool16_t mask, int16_t *out, vint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -12733, 7111, 25587, 23637, -22583, 17938, -11561, 15694, 4308, -3401, 18397, 16503, -10314, -24958, 1591, 18157
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
