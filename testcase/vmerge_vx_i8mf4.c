/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    202, 168, 97, 248, 26, 144, 114, 200, 250, 115, 256, 182, 154, 253, 167, 119
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    81, 194, 71, 47, 161, 184, 161, 179, 145, 102, 87, 96, 21, 60, 227, 131
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf4(size_t avl);
    bool32_t masked[] = {
    1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4 (mask, *in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i8mf4 (data1_v, data2_v, size_t vl);
        void vint32_t __riscv_vse8mf4_v_i8 (vbool8_t mask, int8mf4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    81, 194, 97, 47, 161, 144, 161, 179, 250, 115, 87, 96, 21, 60, 167, 119
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
