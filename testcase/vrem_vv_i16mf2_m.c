/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    55755, 38952, 19317, 12823, 17414, 46345, 60264, 31504, 64390, 64513, 20238, 49330, 31995, 4444, 18744, 3770
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    4460, 38841, 37479, 18980, 5878, 17103, 32045, 53221, 18516, 4856, 60602, 37560, 25818, 25794, 24317, 57831
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    58142, 8076, 48113, 62198, 37648, 40157, 60705, 8089, 39987, 8339, 24669, 17853, 14237, 40277, 29450, 9776
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    58142, 8076, 18162, 62198, 37648, 17103, 32045, 8089, 39987, 4856, 24669, 37560, 25818, 40277, 29450, 1281
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
