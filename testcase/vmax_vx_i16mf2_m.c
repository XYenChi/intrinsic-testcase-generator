/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    50432, 54507, 64463, 19120, 17054, 3413, 64198, 45308, 32832, 23867, 38937, 31580, 46684, 60677, 1874, 61959
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    30189, 6989, 36202, 20781, 37129, 3441, 2634, 19080, 25219, 21035, 40872, 4054, 49368, 55609, 49329, 3133
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    39694, 30251, 50120, 4042, 55613, 52618, 559, 4205, 10841, 9082, 59612, 146, 14390, 21188, 4281, 51850
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    39694, 54507, 64463, 4042, 37129, 3441, 64198, 4205, 10841, 23867, 59612, 146, 14390, 60677, 4281, 61959
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
