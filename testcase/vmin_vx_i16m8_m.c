/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    55541, 25227, 64897, 63477, 18355, 7890, 41681, 34194, 14779, 14973, 27634, 44980, 7905, 32090, 61390, 34453
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    59158, 23666, 7910, 50411, 52953, 35555, 20408, 20076, 53371, 3077, 30090, 10632, 27947, 62198, 60571, 5435
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    61049, 31795, 4358, 1550, 11674, 23702, 13642, 47906, 38601, 32491, 27040, 12091, 52813, 58408, 25086, 42126
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    61049, 31795, 4358, 63477, 11674, 35555, 13642, 34194, 38601, 14973, 27040, 44980, 52813, 58408, 25086, 34453
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
