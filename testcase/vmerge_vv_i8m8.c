/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    176, 158, 148, 255, 204, 52, 0, 93, 85, 167, 247, 199, 244, 238, 213, 107
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    67, 74, 127, 16, 20, 252, 119, 82, 82, 98, 212, 179, 82, 235, 110, 181
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m8(size_t avl);
    bool1_t masked[] = {
    0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0
    };
    const bool1_t *mask = &masked[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8 (mask, *in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i8m8 (data1_v, data2_v, size_t vl);
        void vint1_t __riscv_vse8m8_v_i8 (vbool8_t mask, int8m8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    176, 74, 127, 255, 20, 252, 0, 82, 85, 98, 212, 199, 82, 235, 213, 107
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
