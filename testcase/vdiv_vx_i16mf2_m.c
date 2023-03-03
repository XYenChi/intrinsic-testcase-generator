/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    12057, 31279, 65347, 28372, 17229, 10672, 44264, 17295, 22275, 37141, 22089, 63776, 49184, 17172, 55220, 10406
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    16862, 28026, 58594, 41640, 10742, 9149, 10947, 63917, 7199, 48284, 40702, 33349, 2183, 49216, 22696, 65028
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    3672, 64546, 19202, 31550, 13113, 24533, 20713, 31133, 23890, 45545, 41976, 24731, 17125, 31031, 64801, 37981
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    1, 0, 0, 31550, 0, 24533, 0, 31133, 0, 1, 1, 0, 0, 2, 0, 6
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
