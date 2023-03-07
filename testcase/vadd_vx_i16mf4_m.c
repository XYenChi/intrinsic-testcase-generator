/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    32714, -25980, -4072, -12189, 20864, -31417, -18347, 2934, 30290, 8409, -10079, 575, -17685, 25019, 13745, 7450
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -32341, 5278, 13690, 25256, 32492, 9704, -24154, -23966, -32171, 16628, 9544, -12755, -7989, -16388, -27228, 26283
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const int out_data[] = {
    -10669, 2997, -21723, 26108, -10107, 19942, 16687, -28833, -18008, 13443, 5891, -31694, 14553, 25128, 14490, -18233
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16mf4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf4 (bool16_t mask, int16_t *out, vint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -10669, 2998, -21723, 26109, -10106, 19942, 16688, -28832, -18007, 13443, 5892, -31693, 14553, 25129, 14491, -18232
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
