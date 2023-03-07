/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    2782, -9122, 14194, -12874, 5272, 4451, -26378, 18006, -19361, 8559, -31611, -28768, -4189, -4813, 13954, 63
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -7075, 17137, -6972, 17601, -27874, -16265, 17212, 26967, -22536, 29150, -7665, -31735, -8674, -15938, -29631, 27455
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const int out_data[] = {
    -5943, -14152, -2775, -6375, -7932, 10477, -31000, -2287, 25692, 20813, 29642, -7096, -23392, 26672, 13267, -2962
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16mf4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf4 (bool16_t mask, int16_t *out, vint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -5942, -14151, -2775, -6374, -7931, 10477, -31000, -2287, 25692, 20813, 29642, -7095, -23392, 26673, 13267, -2962
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
