/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    42585, 16490, 36322, 14761, 51299, 47126, 25355, 51708, 62782, 13663, 30020, 58051, 3533, 29822, 15041, 31311
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    27032, 26538, 30975, 46863, 8146, 35094, 45367, 51954, 24749, 9555, 63596, 41061, 5668, 14845, 46734, 8206
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    33440, 29027, 42467, 63041, 30079, 58027, 60588, 45968, 32513, 13219, 36776, 43112, 52897, 38564, 27515, 37003
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    33440, 1, 0, 63041, 0, 58027, 1, 45968, 0, 13219, 2, 0, 1, 38564, 3, 37003
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
