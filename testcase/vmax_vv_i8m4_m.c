/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    17, 210, 6, 167, 63, 213, 221, 227, 212, 157, 0, 169, 27, 135, 196, 250
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    79, 136, 145, 176, 56, 240, 181, 243, 49, 141, 171, 180, 151, 220, 201, 134
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m4(size_t avl);
    const int out_data[] = {
    126, 241, 226, 196, 141, 115, 188, 238, 169, 211, 202, 155, 88, 165, 48, 238
    };
    const int8_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0
    };
    const bool2_t *mask = &masked[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4_m (mask, *in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i8m4_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse8m4_v_i8 (vbool8_t mask, int8m4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    79, 241, 226, 196, 63, 240, 221, 243, 212, 157, 202, 180, 151, 220, 48, 238
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
