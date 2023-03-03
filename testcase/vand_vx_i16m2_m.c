/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    30228, 59362, 40031, 23954, 2716, 10433, 54168, 9643, 6399, 25280, 13200, 18418, 19659, 5476, 57308, 65521
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    27768, 23883, 20846, 887, 12883, 64835, 63822, 13422, 63551, 3205, 49496, 35283, 53902, 56868, 58055, 31165
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    36059, 63582, 10470, 16708, 35515, 59984, 52105, 5306, 45105, 32366, 38570, 57055, 40467, 47318, 37456, 61836
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    36059, 23883, 10470, 16708, 12883, 59984, 52105, 5306, 45105, 3205, 49496, 57055, 53902, 56868, 58055, 31165
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
