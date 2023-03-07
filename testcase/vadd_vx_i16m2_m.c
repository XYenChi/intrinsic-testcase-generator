/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    6470, 20041, 25461, -8284, 14265, -18073, -22959, -12232, -11064, 21255, 5044, -32091, 4136, -4191, -9745, -1370
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    14367, 18039, -22027, -21213, 12669, 23511, 14209, 19316, 7475, 8550, -18579, 12213, 19141, 12984, -18564, -19461
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const int out_data[] = {
    -3128, 27835, -25877, -12336, -28779, 25142, -16974, -30567, -26895, 8597, -1438, -12355, 2596, -4786, 2154, -6568
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m2 (bool16_t mask, int16_t *out, vint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -3127, 27836, -25877, -12335, -28778, 25142, -16973, -30567, -26895, 8598, -1438, -12355, 2596, -4786, 2155, -6567
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
