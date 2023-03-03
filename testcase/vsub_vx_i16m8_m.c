/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    8186, 4236, 7462, 59736, 16472, 897, 49365, 58129, 36080, 20199, 42661, 55523, 26028, 6241, 36005, 29249
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    31473, 19668, 47361, 45544, 51985, 39292, 4700, 43983, 14556, 45334, 34790, 5425, 40966, 28467, 23914, 16411
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    60674, 30040, 51720, 9766, 1764, 37873, 54448, 3677, 5433, 51799, 34587, 23233, 2726, 11733, 63506, 62247
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -23287, 30040, -39899, 9766, -35513, -38395, 54448, 3677, 5433, 51799, 34587, 23233, 2726, -22226, 12091, 12838
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
