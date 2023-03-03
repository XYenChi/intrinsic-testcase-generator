/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    7281, 26569, 27468, 4745, 18669, 41210, 50271, 44134, 37002, 9447, 21639, 12995, 64409, 32085, 36889, 55969
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    32553, 25246, 18185, 35341, 30326, 52863, 55563, 11059, 58145, 61695, 48151, 64946, 54717, 16255, 59746, 39835
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1 (*in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1 (*in2, vl);
    vint16m1_t out_v = __riscv_vle16_v_i16m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i16m1 (data1_v, data2_v, vl);
        void vint16m1_t __riscv_vse16_v_i16 (int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    32553, 26569, 27468, 35341, 30326, 52863, 55563, 44134, 58145, 61695, 48151, 64946, 64409, 32085, 59746, 55969
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
