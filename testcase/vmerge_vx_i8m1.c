/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    236, 166, 158, 139, 138, 243, 133, 122, 248, 13, 241, 36, 240, 157, 226, 226
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    104, 132, 135, 109, 77, 120, 59, 168, 123, 29, 123, 158, 169, 111, 176, 173
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m1(size_t avl);
    bool8_t masked[] = {
    0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1 (mask, *in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i8m1 (data1_v, data2_v, size_t vl);
        void vint8_t __riscv_vse8m1_v_i8 (vbool8_t mask, int8m1_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    236, 132, 158, 109, 77, 243, 133, 122, 248, 13, 241, 36, 169, 111, 176, 226
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
