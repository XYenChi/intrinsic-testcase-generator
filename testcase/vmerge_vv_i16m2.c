/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    53227, 63010, 63920, 43095, 42645, 41068, 47261, 10200, 30761, 27963, 1274, 1010, 982, 16470, 4269, 59765
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    15262, 56126, 6331, 27021, 39615, 49795, 20873, 4127, 54011, 55487, 20996, 39230, 37203, 37481, 16506, 42975
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    bool8_t masked[] = {
    1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i16m2 (data1_v, data2_v, size_t vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    15262, 56126, 6331, 43095, 39615, 41068, 20873, 4127, 30761, 27963, 1274, 39230, 982, 16470, 4269, 59765
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
