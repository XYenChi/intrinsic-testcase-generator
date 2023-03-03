/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    107, 45, 222, 73, 68, 232, 91, 164, 162, 168, 16, 77, 151, 232, 97, 53
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    173, 129, 129, 17, 73, 125, 255, 92, 34, 93, 59, 96, 145, 211, 169, 230
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf2(size_t avl);
    bool16_t masked[] = {
    0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2 (mask, *in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i8mf2 (data1_v, data2_v, size_t vl);
        void vint16_t __riscv_vse8mf2_v_i8 (vbool8_t mask, int8mf2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    107, 45, 222, 73, 73, 232, 255, 164, 162, 168, 59, 77, 145, 211, 169, 230
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
