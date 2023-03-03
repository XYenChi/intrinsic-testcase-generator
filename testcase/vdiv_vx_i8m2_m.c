/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    190, 218, 7, 232, 53, 92, 233, 181, 20, 166, 91, 203, 98, 43, 256, 106
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    176, 142, 27, 42, 61, 47, 246, 196, 7, 234, 198, 135, 4, 203, 224, 136
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m2(size_t avl);
    const int out_data[] = {
    155, 205, 41, 150, 76, 211, 221, 125, 139, 219, 248, 62, 150, 59, 227, 52
    };
    const int8_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, *in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i8m2_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse8m2_v_i8 (vbool8_t mask, int8m2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    155, 0, 3, 150, 1, 211, 1, 1, 139, 219, 248, 0, 0, 4, 227, 1
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
