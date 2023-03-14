/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    34, -22, -70, 114, -67, 50, 70, -60, -101, -4, 54, 110, -63, 124, 6, -20
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    78, -117, -51, 73, -114, 73, -47, -61, 127, 50, -65, -32, -75, 65, 53, -33
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m2(avl);
    const int out_data[] = {
    0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0
    };
    const int8_t *out = &out_data[0];
    uint4_t masked[] = {
    1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0
    };
    const uint4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2_m (mask, in2, vl);
    vint8m2_t out_v = __riscv_vle8_v_i8m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_i8m2 (bool8_t mask, int8_t *out, vint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    112, 0, 0, 187, 0, 0, 23, 135, 26, 1, 0, 1, 118, 1, 59, 0
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
