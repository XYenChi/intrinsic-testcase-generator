/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    40706, 12692, 6851, 52554, 41579, 55308, 53007, 23888, 47813, 33010, 13020, 53348, 25203, 54204, 39840, 22002
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    25493, 36041, 33286, 28044, 19775, 14464, 29833, 41779, 18237, 28460, 31162, 48358, 30947, 31297, 16216, 55980
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    49588, 1406, 46842, 1499, 1074, 8736, 62860, 61079, 7416, 12457, 1569, 53694, 60191, 44517, 58293, 49155
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    15213, -23350, -26435, 24509, 21803, 40844, 23174, -17891, 29575, 4550, -18143, 4990, -5744, 22906, 23624, -33978
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
