/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    60879, 34535, 8530, 54006, 10380, 13189, 26821, 24697, 29496, 52021, 6918, 5175, 38166, 21711, 28169, 28236
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    63247, 28133, 47477, 5826, 24519, 38685, 16327, 33233, 21052, 27458, 8387, 18418, 37896, 6988, 8967, 54583
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    42977, 37312, 24938, 17933, 527, 23488, 53352, 22635, 14430, 31482, 4019, 45338, 37465, 61161, 32935, 15241
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    42977, 37312, 4827, 17933, 3759, 12307, 53352, 8536, 21052, 31482, 4019, 2893, 37896, 61161, 8967, 15241
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
