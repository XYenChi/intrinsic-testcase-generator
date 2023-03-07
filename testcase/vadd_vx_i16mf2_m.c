/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -32217, -29792, -28686, 8833, -14677, 5292, 8072, -8759, 14667, 31461, 29532, -5597, 15246, 12563, 16791, 18451
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    28371, 20435, -3827, 11726, -29225, -7389, -6345, 3807, -16981, -15738, -22622, 13362, 2436, 7861, -1591, -15682
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const int out_data[] = {
    21506, -7908, -4607, -9250, 3986, 9533, 21911, -4334, 19602, 23985, 11466, 22383, 27306, -1622, 20053, -18772
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf2 (bool16_t mask, int16_t *out, vint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    21507, -7908, -4606, -9249, 3986, 9533, 21911, -4334, 19603, 23985, 11467, 22383, 27307, -1621, 20054, -18772
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
