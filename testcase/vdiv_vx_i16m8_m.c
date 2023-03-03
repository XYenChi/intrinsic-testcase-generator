/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    62514, 48642, 51181, 33215, 31625, 50016, 64943, 64616, 54670, 30527, 32664, 26922, 45013, 14276, 8627, 57413
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    1447, 45893, 6164, 56360, 63916, 46416, 20178, 28314, 1283, 32797, 13105, 37633, 29519, 52990, 41296, 45235
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    39930, 56970, 37088, 12920, 48000, 17286, 14202, 397, 31233, 20847, 24523, 32768, 52967, 13190, 48515, 63078
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    39930, 0, 0, 1, 2, 17286, 14202, 0, 0, 1, 24523, 32768, 0, 3, 48515, 63078
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
