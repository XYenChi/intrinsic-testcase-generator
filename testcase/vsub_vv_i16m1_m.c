/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    58440, 41571, 23759, 853, 35706, 12148, 33552, 24114, 6675, 4073, 31960, 40848, 43488, 37094, 3486, 22921
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    20631, 10045, 18511, 51019, 24978, 58104, 34673, 33553, 14268, 32048, 40681, 64998, 52649, 19841, 41902, 6230
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    27379, 62896, 50290, 33027, 41572, 60578, 12168, 3721, 52125, 41302, 53895, 8133, 14605, 36743, 927, 49081
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    37809, 62896, 50290, 33027, 10728, 60578, -1121, 3721, 52125, 41302, 53895, 8133, -9161, 36743, 927, 49081
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
