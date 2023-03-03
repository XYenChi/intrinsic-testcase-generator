/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    91, 145, 141, 17, 129, 215, 225, 101, 234, 34, 112, 243, 195, 214, 180, 181
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    231, 212, 105, 132, 66, 23, 214, 75, 176, 94, 241, 60, 248, 224, 136, 210
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m1(size_t avl);
    const int out_data[] = {
    142, 102, 35, 103, 213, 104, 148, 80, 0, 136, 14, 194, 147, 107, 5, 113
    };
    const int8_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1_m (mask, *in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i8m1_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse8m1_v_i8 (vbool8_t mask, int8m1_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -140, -68, 35, -116, 63, 192, 10, 26, 57, -60, -129, 183, -53, -10, 43, -30
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
