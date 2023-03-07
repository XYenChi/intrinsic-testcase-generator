/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    936, -227, 24961, -31391, 21113, 30832, 10254, -10292, -22979, 31545, -14690, -3688, -17778, 22371, -780, 15676
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    8099, -12166, -30119, -10949, 11644, 18318, -4291, -2533, -32248, -15606, -13441, -24956, 25037, 11769, -2315, -12398
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const int out_data[] = {
    16639, 21910, -28591, -1648, -7450, 26162, -8598, 28019, 25219, 21209, 15483, -14245, -26693, -18867, -3944, 13415
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u16mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf2 (bool16_t mask, int16_t *out, vint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    16639, 21911, -28591, -1647, -7449, 26162, -8598, 28020, 25220, 21210, 15483, -14245, -26693, -18867, -3944, 13415
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
