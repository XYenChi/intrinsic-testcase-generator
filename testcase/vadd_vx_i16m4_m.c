/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    13186, 22432, 17255, 14574, 22641, 22970, 870, 21831, -1916, 8627, -30822, 2224, -12439, -31581, 19531, -24891
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -27809, -27623, -3195, 18506, -22464, -14415, 7549, 3416, 10579, -26451, 20475, 32482, 7362, -16586, -28219, -14806
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const int out_data[] = {
    10728, 7504, 9435, -10251, -12249, 7052, -5730, -1284, -14695, -28768, -833, -8556, 32558, -22822, 8835, -22322
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m4 (bool16_t mask, int16_t *out, vint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    10729, 7505, 9436, -10251, -12249, 7052, -5729, -1283, -14695, -28768, -833, -8555, 32558, -22822, 8836, -22322
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
