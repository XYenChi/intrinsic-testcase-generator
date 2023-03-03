/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    176, 144, 95, 102, 124, 235, 87, 252, 74, 151, 10, 175, 155, 90, 127, 69
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    203, 78, 164, 29, 51, 163, 148, 234, 113, 240, 105, 105, 9, 195, 94, 53
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m4(size_t avl);
    bool2_t masked[] = {
    0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0
    };
    const bool2_t *mask = &masked[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4 (mask, *in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i8m4 (data1_v, data2_v, size_t vl);
        void vint2_t __riscv_vse8m4_v_i8 (vbool8_t mask, int8m4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    176, 144, 164, 29, 51, 235, 87, 234, 113, 240, 10, 105, 155, 195, 127, 69
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
