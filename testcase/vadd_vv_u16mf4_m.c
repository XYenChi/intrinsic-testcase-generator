/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    12531, 11022, 21971, 21187, -6984, -28758, -25501, 12500, -207, -23711, 6303, -3950, -30046, 742, 27296, 22767
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    8690, 22299, -18642, 19183, 17869, 24360, 1450, -3570, -12149, 1047, -22654, -11310, 23436, -10249, 17734, -26956
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const int out_data[] = {
    -19116, -31191, -4562, 210, -2940, 22067, -6373, -13667, -2587, -28713, -10394, -20832, -5849, 30439, -9843, 22722
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u16mf4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf4 (bool16_t mask, int16_t *out, vint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -19115, -31190, -4561, 211, -2940, 22068, -6373, -13666, -2587, -28712, -10394, -20831, -5848, 30440, -9843, 22723
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
