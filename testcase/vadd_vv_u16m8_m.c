/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    8230, 14786, 22899, -20086, 14017, -25274, 24558, 29723, -18673, 11764, 13106, -13449, 24954, -23873, 10339, 27773
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    18466, -13443, -3713, 5943, -6745, 17695, 24199, 14716, 6569, 7514, 20595, -31436, -3618, 14794, 6314, 2353
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const int out_data[] = {
    9546, -11223, -297, -32384, -17122, 18287, -16508, 6836, -7788, 16444, 33, -27015, -24092, 1326, 13784, 13800
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u16m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m8 (bool16_t mask, int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    9547, -11223, -296, -32383, -17121, 18287, -16508, 6836, -7787, 16444, 33, -27014, -24092, 1327, 13784, 13800
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
