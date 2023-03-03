/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    28502, 49395, 42132, 37498, 41484, 62845, 36688, 27877, 1015, 34830, 60781, 12638, 45094, 49277, 3538, 15948
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    61542, 63585, 54493, 1471, 61862, 63617, 5458, 6186, 40887, 30740, 59865, 30252, 28029, 60185, 34516, 47022
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    54330, 12605, 6661, 39530, 4655, 48222, 15175, 54771, 18940, 28293, 22265, 35539, 5323, 9203, 23598, 35890
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -33040, -14190, -12361, 39530, 4655, -772, 31230, 54771, 18940, 28293, 916, 35539, 5323, 9203, 23598, 35890
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
