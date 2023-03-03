/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    64810, 28003, 436, 48023, 22229, 38646, 24096, 32684, 24860, 35426, 32805, 43953, 12750, 59095, 8473, 4306
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    23330, 16763, 14090, 28471, 22516, 12728, 61644, 63186, 14864, 64013, 9578, 61261, 11894, 15120, 23880, 57913
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    49976, 36058, 55581, 56026, 2828, 6012, 52798, 13384, 4021, 25215, 62178, 60548, 62908, 59342, 39271, 57107
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    41480, 36058, 55581, 56026, -287, 6012, -37548, -30502, 4021, 25215, 23227, 60548, 856, 43975, -15407, 57107
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
