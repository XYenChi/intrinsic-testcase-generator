/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    1700, -14098, -29669, 4287, 21626, 1448, -11610, 16291, -24872, 29237, -20283, 9247, -21583, 22048, 8707, 31972
    };
    const int16_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const int out_data[] = {
    26756, -20986, -9921, -11605, 11969, 4393, -22972, -17039, -27306, -1239, 12752, -9728, -21741, 20545, 29929, -1663
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, in1, vl);
    vint16m1_t out_v = __riscv_vle16_v_i16m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_16m1 (mask, data1_v, vl);
        void __riscv_vse16_v_i16m1 (bool16_t mask, int16_t *out, vint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -1700, 14098, 29669, -4287, -21626, -1448, 11610, -16291, 24872, -29237, 20283, -9247, 21583, -22048, -8707, -31972
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
