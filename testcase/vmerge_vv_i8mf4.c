/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    182, 115, 148, 118, 169, 212, 213, 226, 24, 157, 196, 143, 99, 119, 21, 255
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    7, 144, 229, 114, 93, 105, 241, 110, 66, 198, 129, 170, 19, 1, 50, 108
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf4(size_t avl);
    bool32_t masked[] = {
    0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4 (mask, *in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i8mf4 (data1_v, data2_v, size_t vl);
        void vint32_t __riscv_vse8mf4_v_i8 (vbool8_t mask, int8mf4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    182, 144, 229, 114, 93, 212, 213, 226, 66, 157, 129, 143, 99, 119, 21, 255
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
