/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    19966, 11625, 19068, 8071, 54752, 10038, 43857, 91, 26601, 56627, 12808, 21591, 35826, 3837, 53205, 5262
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    64742, 38646, 61967, 47255, 42381, 63332, 50481, 36140, 40753, 14749, 4836, 53503, 35941, 58045, 37107, 61204
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    4180, 12753, 41705, 36993, 48001, 41629, 27028, 6401, 7622, 52131, 31987, 34550, 41257, 45091, 11869, 12064
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    64742, 38646, 41705, 36993, 54752, 41629, 27028, 6401, 40753, 56627, 12808, 53503, 41257, 58045, 11869, 12064
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
