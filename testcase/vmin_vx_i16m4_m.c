/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    50660, 43769, 34775, 40017, 18421, 32448, 24321, 12767, 46381, 42034, 12163, 35752, 26575, 8624, 6722, 63683
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    21234, 64487, 62778, 12768, 47141, 16089, 64074, 2230, 29895, 18269, 6093, 51277, 59682, 3082, 44875, 5855
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    27788, 49626, 48669, 11744, 61380, 39381, 15625, 62029, 14547, 27276, 54205, 57197, 12232, 29235, 34027, 26814
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    50660, 49626, 62778, 40017, 47141, 32448, 64074, 12767, 14547, 27276, 12163, 57197, 12232, 8624, 44875, 26814
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
