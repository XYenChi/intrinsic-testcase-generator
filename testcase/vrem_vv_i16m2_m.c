/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    27832, 23631, 48023, 41978, 54861, 4493, 19627, 3590, 40514, 15867, 34952, 52941, 30768, 61738, 54300, 31972
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    21834, 54609, 44749, 20270, 18395, 21908, 62367, 11643, 8049, 160, 61449, 20899, 31038, 31371, 7980, 52320
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    57040, 51015, 65172, 2922, 62642, 39232, 62960, 53638, 5795, 3213, 2130, 41516, 8214, 59328, 55375, 18019
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    21834, 7347, 65172, 2922, 62642, 39232, 3486, 53638, 5795, 3213, 26497, 41516, 270, 31371, 7980, 20348
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
