/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    27659, -27307, 10859, 9190, -20806, -1119, 29686, 14795, -6183, -27415, 23244, 8214, 96, -11235, -31028, 18881
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -11458, 3470, 13467, -2852, -29517, 13041, -23363, 1965, -21205, -21864, -12859, -6112, -3747, 10334, -30597, -20504
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const int out_data[] = {
    -32543, -16173, 31877, 11417, 5548, -10929, -3177, -16638, 16893, -12569, -29976, 10175, -22459, -31420, 14705, -26650
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u16m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m2 (bool16_t mask, int16_t *out, vint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -32543, -16172, 31878, 11417, 5549, -10929, -3176, -16638, 16894, -12569, -29976, 10176, -22459, -31419, 14706, -26649
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
