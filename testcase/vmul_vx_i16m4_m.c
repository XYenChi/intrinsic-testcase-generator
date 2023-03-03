/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    4183, 7219, 23086, 10004, 24714, 40947, 13017, 17438, 57798, 60407, 3081, 36392, 31358, 41790, 48239, 18980
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    3426, 40606, 7613, 38799, 50566, 53921, 9339, 47822, 43769, 43993, 10747, 32950, 26075, 56841, 60470, 45839
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    11075, 15978, 58079, 11955, 22638, 633, 40489, 49412, 9099, 53503, 53252, 3008, 35933, 2158, 56296, 52387
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    11075, 15978, 175753718, 388145196, 1249688124, 633, 121565763, 833920036, 2529760662, 2657485151, 53252, 1199116400, 817659850, 2158, 2917012330, 870024220
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
