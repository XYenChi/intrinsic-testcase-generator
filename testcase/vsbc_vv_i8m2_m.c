/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    112, 198, 9, 243, 82, 123, 62, 45, 188, 172, 16, 74, 246, 59, 202, 233
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    28, 20, 45, 66, 232, 48, 167, 99, 56, 184, 127, 118, 108, 50, 220, 73
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m2(size_t avl);
    const int out_data[] = {
    151, 45, 103, 100, 89, 200, 92, 35, 88, 187, 112, 149, 70, 191, 256, 48
    };
    const int8_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, *in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i8m2_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse8m2_v_i8 (vbool8_t mask, int8m2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    83, 177, -36, 176, -150, 74, -105, -54, 131, -13, -111, -45, 137, 9, -18, 160
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
