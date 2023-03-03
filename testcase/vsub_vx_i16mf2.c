/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    62081, 7360, 39828, 44232, 14621, 37708, 49913, 12440, 29003, 50975, 26257, 19308, 64884, 58624, 12127, 26083
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    7786, 29100, 36746, 43763, 33266, 57270, 27692, 38419, 61194, 55597, 60934, 23640, 45000, 12046, 49990, 18467
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (*in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (*in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u16mf2 (data1_v, data2_v, vl);
        void vint16mf2_t __riscv_vse16_v_i16 (int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    54295, -21740, 3082, 469, -18645, -19562, 22221, -25979, -32191, -4622, -34677, -4332, 19884, 46578, -37863, 7616
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
