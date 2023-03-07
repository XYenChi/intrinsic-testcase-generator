/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    21374, -32434, 13030, -24277, -26536, 4057, -7218, -2464, -9196, 19963, 16096, -15854, -14453, -950, -15049, -14929
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -31873, -2833, 4967, 31515, 31417, -10200, -1167, 20758, 30608, -11341, 7005, -24389, 16914, -6107, -120, 10696
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const int out_data[] = {
    -12370, -11858, 7500, -14443, -30219, -15291, 9300, 9632, -9055, -7394, -18392, 8501, -735, 3077, 26593, -21233
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m8 (bool16_t mask, int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -12369, -11858, 7501, -14443, -30219, -15291, 9300, 9633, -9054, -7393, -18391, 8502, -734, 3077, 26593, -21232
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
