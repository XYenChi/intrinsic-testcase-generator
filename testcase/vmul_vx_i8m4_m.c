/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    75, 227, 88, 222, 216, 124, 35, 166, 233, 174, 62, 43, 27, 138, 17, 140
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    0, 244, 147, 135, 137, 15, 256, 248, 2, 86, 189, 81, 249, 36, 11, 96
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m4(size_t avl);
    const int out_data[] = {
    245, 61, 240, 135, 181, 104, 92, 237, 166, 240, 128, 14, 80, 218, 5, 168
    };
    const int8_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0
    };
    const bool2_t *mask = &masked[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4_m (mask, *in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i8m4_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse8m4_v_i8 (vbool8_t mask, int8m4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    0, 61, 12936, 135, 181, 104, 92, 41168, 166, 14964, 11718, 14, 6723, 4968, 187, 168
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
