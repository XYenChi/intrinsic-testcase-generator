/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -7206, 28257, 23613, 6309, 15043, -4388, 16670, 30242, -16618, -3960, -28040, -16514, 6326, 10777, 30006, -25037
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -29683, 25277, 22723, 15170, 2237, 8073, 21166, -19, 7318, -19849, -10673, 20837, 22569, 29535, 21392, -31175
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const int out_data[] = {
    3240, -3491, 16814, 30787, 20861, 3794, 20113, 26390, -16772, 2671, 20881, 18321, -7193, 27921, -3692, -5149
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u16m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m2 (bool16_t mask, int16_t *out, vint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    3241, -3491, 16814, 30787, 20862, 3795, 20114, 26391, -16772, 2671, 20881, 18321, -7192, 27921, -3691, -5148
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
