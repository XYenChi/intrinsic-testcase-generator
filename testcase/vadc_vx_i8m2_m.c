/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    101, 162, 188, 2, 68, 104, 197, 139, 45, 240, 71, 128, 173, 101, 54, 254
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    159, 221, 62, 49, 166, 102, 23, 173, 231, 118, 75, 165, 51, 215, 251, 160
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m2(size_t avl);
    const int out_data[] = {
    62, 241, 76, 62, 177, 99, 152, 167, 142, 60, 60, 47, 2, 33, 135, 75
    };
    const int8_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, *in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint4_t __riscv_vse8m2_v_i8 (vbool8_t mask, int8m2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    260, 384, 250, 52, 235, 207, 221, 313, 276, 358, 146, 294, 225, 316, 306, 414
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
