/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    61, 69, 100, 57, 174, 81, 56, 94, 79, 64, 202, 140, 175, 12, 8, 162
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    173, 151, 111, 227, 220, 41, 246, 128, 234, 24, 174, 93, 210, 166, 11, 209
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf4(size_t avl);
    const int out_data[] = {
    163, 243, 157, 249, 253, 215, 2, 165, 234, 149, 85, 107, 116, 222, 130, 251
    };
    const int8_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, *in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32_t __riscv_vse8mf4_v_i8 (vbool8_t mask, int8mf4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    163, 243, 111, 227, 253, 215, 2, 128, 234, 24, 85, 107, 116, 222, 130, 209
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
