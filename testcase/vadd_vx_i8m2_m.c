/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    148, 63, 109, 251, 7, 145, 178, 29, 38, 61, 5, 168, 185, 130, 224, 68
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    92, 184, 129, 83, 219, 215, 13, 117, 128, 21, 8, 147, 200, 103, 190, 70
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m2(size_t avl);
    const int out_data[] = {
    27, 220, 132, 174, 16, 175, 76, 90, 41, 229, 180, 184, 161, 203, 171, 146
    };
    const int8_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, *in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i8m2_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse8m2_v_i8 (vbool8_t mask, int8m2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    27, 220, 238, 334, 16, 175, 76, 90, 166, 229, 13, 184, 385, 233, 414, 146
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
