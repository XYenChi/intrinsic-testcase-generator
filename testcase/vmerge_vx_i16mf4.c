/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    40717, 60392, 20346, 14956, 9273, 37716, 64757, 62891, 29448, 8096, 34870, 30274, 32788, 4337, 10104, 15624
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    39434, 34098, 64105, 28401, 51107, 40225, 14786, 10580, 12878, 25963, 6857, 56271, 48049, 14261, 54229, 46864
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    bool64_t masked[] = {
    0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i16mf4 (data1_v, data2_v, size_t vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    40717, 60392, 20346, 14956, 9273, 40225, 64757, 10580, 12878, 8096, 6857, 56271, 48049, 4337, 54229, 15624
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
