/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    166, 212, 67, 100, 86, 223, 191, 42, 93, 2, 170, 242, 210, 242, 117, 187
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    231, 33, 250, 6, 163, 42, 132, 228, 121, 191, 34, 236, 234, 141, 150, 28
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m8(size_t avl);
    const int out_data[] = {
    160, 159, 209, 157, 19, 128, 68, 212, 122, 8, 123, 141, 29, 161, 51, 81
    };
    const int8_t *out = &out_data[0];
    bool1_t masked[] = {
    1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0
    };
    const bool1_t *mask = &masked[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8_m (mask, *in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i8m8_m (mask, data1_v, data2_v, vl);
        void vint1_t __riscv_vse8m8_v_i8 (vbool8_t mask, int8m8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    38346, 159, 209, 600, 19, 9366, 25212, 9576, 11253, 382, 123, 141, 49140, 161, 51, 81
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