/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -29225, 9321, -25475, 9527, -18709, 25663, 2507, 22460, -6421, -2158, 20707, -16611, -3789, -11180, -3860, 13532
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    6412, 6648, -13270, -22423, -4564, -15856, -10397, 19513, -24557, 10722, 26898, 15565, -27707, -26802, -30261, 14455
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const int out_data[] = {
    -16997, 10375, -966, -4508, 20832, 25432, -15242, -31558, 24839, -2611, 17751, -10228, -29025, -10708, -1532, 23837
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m8 (bool16_t mask, int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -16997, 10375, -965, -4508, 20832, 25432, -15241, -31558, 24839, -2611, 17752, -10228, -29024, -10707, -1531, 23837
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
